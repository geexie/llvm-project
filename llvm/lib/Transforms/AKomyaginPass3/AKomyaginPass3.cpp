#include "llvm/Transforms/AKomyaginPass3/AKomyaginPass3.h"
#include "llvm/Analysis/AKomyaginAnalysis.h"
#include "llvm/Analysis/AKomyaginLoopAnalysis.h"
#define DEBUG_TYPE "AKomyaginPass3"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

STATISTIC(totalPow, "Number of Pow()");
STATISTIC(totalAdd, "Number of 'Add'");
STATISTIC(totalMul, "Number of 'Mul'");
STATISTIC(totalLoopsVectorizable, "Number of vectorizable loops");


using namespace llvm;

static void handleLoop(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    if (L->isInnermost()) {
        auto& result = LAM.getResult<AKomyaginLoopAnalysis>(*L, LSAR);
        if (result.InvUpd == 1) {
            totalLoopsVectorizable++;
        }
    }
    else {
        for (Loop* subLoop : L->getSubLoops()) {
            handleLoop(subLoop, LAM, LSAR);
        }
    }
}

PreservedAnalyses AKomyaginPass3::run(Function& F, FunctionAnalysisManager& AM) {

 auto& result = AM.getResult<AKomyaginAnalysis>(F);
    totalAdd += result.totalAdd;
    totalMul += result.totalMul;
    totalPow += result.totalPow;

    result.print(errs());

    auto& LI = AM.getResult<LoopAnalysis>(F);
    auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

    auto& AA = AM.getResult<AAManager>(F);
    AssumptionCache &AC = AM.getResult<AssumptionAnalysis>(F);
    DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
    ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    TargetLibraryInfo &TLI = AM.getResult<TargetLibraryAnalysis>(F);
    TargetTransformInfo &TTI = AM.getResult<TargetIRAnalysis>(F);
    LoopStandardAnalysisResults AR = {AA , AC, DT, LI, SE, TLI, TTI, nullptr, nullptr};

    for (auto& L : LI)
        handleLoop(L, LAM, AR);

    return PreservedAnalyses::all();
}