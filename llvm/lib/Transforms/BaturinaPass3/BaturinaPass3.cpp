#include "llvm/Transforms/BaturinaPass3/BaturinaPass3.h"
#include "llvm/Analysis/BaturinaAnalysis.h"
#include "llvm/Analysis/BaturinaLoopAnalysis.h"

#define DEBUG_TYPE "baturinaPass3"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

using namespace llvm;

STATISTIC(TotalAdd, "Number of add");
STATISTIC(TotalMul, "Number of mul");
STATISTIC(TotalPow, "Number of pow");
STATISTIC(VectorizableLoops, "Number of vectorizable loops");


static void loopsProc(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    if (L->isInnermost()) {
        auto& result = LAM.getResult<BaturinaLoopAnalysis>(*L, LSAR);
        if (result.updCnt == 1) {
            VectorizableLoops++;
        }
    }
    else {
        for (Loop* subLoop : L->getSubLoops()) {
        loopsProc(subLoop, LAM, LSAR);
        }
    }
}

PreservedAnalyses BaturinaPass3::run(Function &F, FunctionAnalysisManager &FAM) {

    auto& result = FAM.getResult<BaturinaAnalysis>(F);
    TotalAdd += result.totalAdd;
    TotalMul += result.totalMul;
    TotalPow += result.totalPow;

    result.print(errs());

    auto& LA = FAM.getResult<LoopAnalysis>(F);
    auto& LAM = FAM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

    auto& AA = FAM.getResult<AAManager>(F);
    AssumptionCache &AC = FAM.getResult<AssumptionAnalysis>(F);
    DominatorTree &DT = FAM.getResult<DominatorTreeAnalysis>(F);
    ScalarEvolution &SE = FAM.getResult<ScalarEvolutionAnalysis>(F);
    TargetLibraryInfo &TLI = FAM.getResult<TargetLibraryAnalysis>(F);
    TargetTransformInfo &TTI = FAM.getResult<TargetIRAnalysis>(F);
    LoopStandardAnalysisResults LSAR = {AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr};

    for (auto& loop : LA)
        loopsProc(loop, LAM, LSAR);

    return PreservedAnalyses::all();
}