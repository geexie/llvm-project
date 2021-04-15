#include "llvm/Analysis/pvia.h"
#include "llvm/Analysis/pvila.h"
#include "llvm/Transforms/pvi3/pvi3.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/Dominators.h"

using namespace llvm;

STATISTIC(AddCounter, "Number of add");
STATISTIC(MulCounter, "Number of mul");
STATISTIC(PowCounter, "Number of pow");
STATISTIC(VectorizableLoops, "Number of vectorizable loops");

void loopsProc(Loop *L, LoopAnalysisManager &LAM,
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

  auto &result = AM.getResult<pvia>(F);
  AddCounter += result.Addcounter;
  MulCounter += result.Mulcounter;
  PowCounter += result.Powcounter;

  result.print(errs());

  auto &LA = AM.getResult<LoopAnalysis>(F);
  auto &LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

  auto &AA = AM.getResult<AAManager>(F);
  AssumptionCache &AC = AM.getResult<AssumptionAnalysis>(F);
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
  ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
  TargetLibraryInfo &TLI = AM.getResult<TargetLibraryAnalysis>(F);
  TargetTransformInfo &TTI = AM.getResult<TargetIRAnalysis>(F);
  LoopStandardAnalysisResults LSAR = {AA,  AC,  DT,      LA,     SE,
                                      TLI, TTI, nullptr, nullptr};

  for (auto &loop : LA)
    loopsProc(loop, LAM, LSAR);

  return PreservedAnalyses::all();
}