#include "llvm/Transforms/PankratovaTransformPass/PankratovaTransformPass.h"

using namespace llvm;

#define DEBUG_TYPE "transform pass by Pankratova"

STATISTIC(TotalVectorizableLoops, "Number of Vectorizable Loops");
STATISTIC(TotalBlocks, "Number of Basic blocks");
STATISTIC(TotalAdd, "Number of Add instructions");
STATISTIC(TotalMul, "Number of Mul instructions");


namespace {

void handleLoops(Loop *L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& AR) {
    if (L->isInnermost()) {
        auto& result = LAM.getResult<PankratovaLoopAnalysis>(*L, AR);
        if (result.count == 1) {
            TotalVectorizableLoops++;
        }
    }
    for (Loop* subLoop : L->getSubLoops()) {
        handleLoops(subLoop, LAM, AR);
    }
}

}


PreservedAnalyses PankratovaTransformPass::run(Function &F, FunctionAnalysisManager &AM) {

    auto& result = AM.getResult<PankratovaAnalysis>(F);

    TotalAdd += result.totalAdd;
    TotalMul += result.totalMul;
    TotalBlocks += result.totalBlocks;

    auto& LA = AM.getResult<LoopAnalysis>(F);
    auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();
    auto& AA = AM.getResult<AAManager>(F);
    auto& AC = AM.getResult<AssumptionAnalysis>(F);
    auto& DT = AM.getResult<DominatorTreeAnalysis>(F);
    auto& SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    auto& TLI = AM.getResult<TargetLibraryAnalysis>(F);
    auto& TTI = AM.getResult<TargetIRAnalysis>(F);

    LoopStandardAnalysisResults AR = {AA, AC, DT, LA, SE, TLI, TTI, nullptr, nullptr};
    for (auto& loop : LA) {
        handleLoops(loop, LAM, AR);
    }
    return PreservedAnalyses::all();
}
