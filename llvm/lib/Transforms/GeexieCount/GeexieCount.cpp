//===-- GeexieCount.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/GeexieCount/GeexieCount.h"
#include "llvm/Analysis/FunctionPropertiesAnalysis.h"
#include "llvm/Analysis/GeexieFunctionAnalysis.h"
#include "llvm/Analysis/LoopAnalysisManager.h"

// for loop analysis
#include "llvm/Analysis/GeexieLoopAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"

#define DEBUG_TYPE "geexie-count"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

STATISTIC(TotalFuncs, "Number of functions");
STATISTIC(TotalBBs, "Number of basic blocks");
STATISTIC(TotalLoops, "Number of loops");
STATISTIC(TotalMulAndAdds, "Number of multiply and add instructions");
STATISTIC(TotalPhis, "Number of Phi instructions");
STATISTIC(TotalLoopsVectorizableIV, "Number of intermost loops in a canonical form with a single induction variable update");

static void handleLoop(Loop *L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& AR) {
  if (L->isInnermost()) {
    auto& GLA = LAM.getResult<GeexieLoopAnalysis>(*L, AR);
    if (GLA.InvUpdatesCount == 1) {
      TotalLoopsVectorizableIV++;
    }
  }

  for (Loop *SL : L->getSubLoops()) {
    handleLoop(SL, LAM, AR);
  }
}

PreservedAnalyses GeexieCountPass::run(Function &F, FunctionAnalysisManager &AM) {
  // count functions
  TotalFuncs++;

  // get standart function properties and print them to error stream
  // auto& FP = AM.getResult<FunctionPropertiesAnalysis>(F);
  // FP.print(errs());

  // get custom analysis
  auto& GFP = AM.getResult<GeexieFunctionAnalysis>(F);

  // append analysis to total counts
  TotalBBs += GFP.BBsCount;
  TotalMulAndAdds += GFP.MulAndAddsCount;
  TotalPhis += GFP.PhisCount;
  TotalLoops += GFP.LoopsCount;

    // // count loops within a function
  auto& LI = AM.getResult<LoopAnalysis>(F);
  auto &LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

  auto &AA = AM.getResult<AAManager>(F);
  auto &AC = AM.getResult<AssumptionAnalysis>(F);
  auto &DT = AM.getResult<DominatorTreeAnalysis>(F);
  auto &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
  auto &TLI = AM.getResult<TargetLibraryAnalysis>(F);
  auto &TTI = AM.getResult<TargetIRAnalysis>(F);
  LoopStandardAnalysisResults AR = {AA, AC, DT, LI, SE, TLI, TTI, nullptr, nullptr};
  for (auto& L : LI) {
    handleLoop(L, LAM, AR);
  }

  return PreservedAnalyses::all();
}
