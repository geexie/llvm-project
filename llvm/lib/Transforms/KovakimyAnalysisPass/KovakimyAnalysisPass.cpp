#pragma once

#include "llvm/Transforms/KovakimyAnalysisPass/KovakimyAnalysisPass.h"
#include "llvm/Analysis/KovakimyAnalysis.h"
#include "llvm/Analysis/KovakimyAnalysisLoop.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
using namespace llvm;
#define DEBUG_TYPE "kovakimyanalysispass"

STATISTIC(TotalLoops, "Number of loops");
STATISTIC(CounterAdd, "Number of adds");
STATISTIC(CounterMult, "Number of muls");
STATISTIC(CounterPowfs, "Number of powfs");



void counterLoops(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR)
{
  if (L->isInnermost())
  {
    auto &result = LAM.getResult<KovakimyAnalysisLoop>(*L, LSAR);
	if (result.updates == 1)
	  TotalLoops++;
  }
  else
  {
    for (Loop * loop : L->getSubLoops())
	  counterLoops(loop, LAM, LSAR);
  }
}

PreservedAnalyses KovakimyAnalysisPass::run(Function &F,
                                            FunctionAnalysisManager &AM) 
{
  auto &result = AM.getResult<KovakimyAnalysis>(F);
  CounterAdd   += result.counterAdd;
  CounterMult  += result.counterMul;
  CounterPowfs += result.counterPow;

  result.print(errs());

  auto& LA  = AM.getResult<LoopAnalysis>(F);
  auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

  auto& AA                         = AM.getResult<AAManager>(F);
  AssumptionCache &AC              = AM.getResult<AssumptionAnalysis>(F);
  DominatorTree &DT                = AM.getResult<DominatorTreeAnalysis>(F);
  ScalarEvolution &SE              = AM.getResult<ScalarEvolutionAnalysis>(F);
  TargetLibraryInfo &TLI           = AM.getResult<TargetLibraryAnalysis>(F);
  TargetTransformInfo &TTI         = AM.getResult<TargetIRAnalysis>(F);
  LoopStandardAnalysisResults LSAR = {AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr};

  for (auto& loop : LA)
    counterLoops(loop, LAM, LSAR);

  return PreservedAnalyses::all();
}
  