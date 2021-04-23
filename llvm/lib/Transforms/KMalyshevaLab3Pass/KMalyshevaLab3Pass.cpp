#include "llvm/Analysis/KMalyshevaAnalysis.h"
#include "llvm/Analysis/KMalyshevaLoopAnalysis.h"
#include "llvm/Transforms/KMalyshevaLab3Pass/KMalyshevaLab3Pass.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/Dominators.h"

using namespace llvm;
#define DEBUG_TYPE "KMalyshevaLab3Pass"

STATISTIC(TotAdd, "Number of add instructions");
STATISTIC(TotMul, "Number of mul instructions");
STATISTIC(TotPow, "Number of pow instructions");
STATISTIC(VectorizableLoops, "Number of vectorizable loops");

void loopshandler(Loop *L, LoopAnalysisManager &LAM,
               LoopStandardAnalysisResults &LSAR) {
  if (L->isInnermost()) {
    auto &result = LAM.getResult<KMalyshevaLoopAnalysis>(*L, LSAR);
    if (result.upd_count == 1) {
      VectorizableLoops++;
    }
  } else {
    for (Loop *subLoop : L->getSubLoops()) {
      loopshandler(subLoop, LAM, LSAR);
    }
  }
}

PreservedAnalyses KMalyshevaLab3Pass::run(Function &F, FunctionAnalysisManager &AM) {

  auto &result = AM.getResult<KMalyshevaAnalysis>(F);
  TotAdd += result.countAdd;
  TotMul += result.countMul;
  TotPow += result.countPow;

 

  auto &LA = AM.getResult<LoopAnalysis>(F);
  auto &LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

  auto &AA = AM.getResult<AAManager>(F);
  AssumptionCache &AC = AM.getResult<AssumptionAnalysis>(F);
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
  ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
  TargetLibraryInfo &TLI = AM.getResult<TargetLibraryAnalysis>(F);
  TargetTransformInfo &TTI = AM.getResult<TargetIRAnalysis>(F);
  LoopStandardAnalysisResults LSAR = {AA, AC,DT,LA,SE,TLI, TTI, nullptr, nullptr};

  for (auto &loop : LA)
    loopshandler(loop, LAM, LSAR);

  return PreservedAnalyses::all();
}