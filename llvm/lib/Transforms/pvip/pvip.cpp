#include "llvm/Transforms/pvip/pvip.h"
#define DEBUG_TYPE "pvip"

using namespace llvm;

STATISTIC(FuncsCounter, "Number of functions");
STATISTIC(BasicBlockCounter, "Number of basic blocks");
STATISTIC(AddCounter, "Number of +");
STATISTIC(MulCounter, "Number of *");
STATISTIC(VLoopsCounter, "Number vloops");


void handleLoop(Loop *L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    if(L->isInnermost()) {
      auto &res = LAM.getResult<pvilf>(*L, LSAR);
      if (res.upd_counter == 1) {
          VLoopsCounter++;
       }
    } 
    else {
      for (Loop *SL : L->getSubLoops()) {
        handleLoop(SL, LAM, LSAR);
      }
    }
}

PreservedAnalyses pvilf::run(Function &F, FunctionAnalysisManager &FAM) {

  FuncsCounter++;

  auto &res = FAM.getResult<pvip>(F);
  BasicBlockCounter += res.bbcount;
  AddCounter += res.addcount;
  MulCounter += res.mulcount;

  auto &LA = FAM.getResult<LoopAnalysis>(F);
  auto &LAM = FAM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

  auto &AA = FAM.getResult<AAManager>(F);
  auto &AC = FAM.getResult<AssumptionAnalysis>(F);
  auto &DT = FAM.getResult<DominatorTreeAnalysis>(F);
  auto &SE = FAM.getResult<ScalarEvolutionAnalysis>(F);
  auto &TLI = FAM.getResult<TargetLibraryAnalysis>(F);
  auto &TTI = FAM.getResult<TargetIRAnalysis>(F);

  LoopStandardAnalysisResults LSAR = {AA, AC, DT, LA, SE, TLI, TTI, nullptr, nullptr};
  for (auto& L : LA)
  {
      handleLoop(L, LAM, LSAR);

  }

  return PreservedAnalyses::all();
}