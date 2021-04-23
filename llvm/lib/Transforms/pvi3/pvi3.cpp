#include "llvm/Analysis/pvia.h"
#include "llvm/Analysis/pvila.h"
#include "llvm/Transforms/pvi3/pvi3.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/Dominators.h"

using namespace llvm;

#define DEBUG_TYPE "pvi3"

STATISTIC(AddCounter, "Number of add");
STATISTIC(MulCounter, "Number of mul");
STATISTIC(PowCounter, "Number of pow");
STATISTIC(VectorizableLoops, "Number of vectorizable loops");

static void loopsProc(Loop *L, LoopAnalysisManager &LAM,
               LoopStandardAnalysisResults &LSAR) {
  if (L->isInnermost()) {
    auto &result = LAM.getResult<pvila>(*L, LSAR);
    if (result.updatecounter == 1) {
      VectorizableLoops++;
    }
  } else {
    for (Loop *subLoop : L->getSubLoops()) {
      loopsProc(subLoop, LAM, LSAR);
    }
  }
}

PreservedAnalyses pvi3::run(Function &F,
                                     FunctionAnalysisManager &FAM) {

  auto &result = FAM.getResult<pvia>(F);
  AddCounter += result.Addcounter;
  MulCounter += result.Mulcounter;
  PowCounter += result.Powcounter;

  result.print(errs());

  auto &LA = FAM.getResult<LoopAnalysis>(F);
  auto &LAM = FAM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

  auto &AA = FAM.getResult<AAManager>(F);
  AssumptionCache &AC = FAM.getResult<AssumptionAnalysis>(F);
  DominatorTree &DT = FAM.getResult<DominatorTreeAnalysis>(F);
  ScalarEvolution &SE = FAM.getResult<ScalarEvolutionAnalysis>(F);
  TargetLibraryInfo &TLI = FAM.getResult<TargetLibraryAnalysis>(F);
  TargetTransformInfo &TTI = FAM.getResult<TargetIRAnalysis>(F);
  LoopStandardAnalysisResults LSAR = {AA,  AC,  DT,      LA,     SE,
                                      TLI, TTI, nullptr, nullptr};

  for (auto &loop : LA)
    loopsProc(loop, LAM, LSAR);

  return PreservedAnalyses::all();
}