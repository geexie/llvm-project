#include "llvm/Transforms/AvmusatovPass/AvmusatovPass.h"
#include "llvm/Analysis/AvmusatovAnalysis.h"
#include "llvm/Analysis/AvmusatovLoopAnalysis.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

using namespace llvm;

static void handleLoop(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    if (L->isInnermost()) {
        auto& result = LAM.getResult<AvmusatovLoopAnalysis>(*L, LSAR);
        if (result.updatesCount == 1) {
            totalVectorizableLoopsCount++;
        }
    }
    else {
        for (Loop* subLoop : L->getSubLoops()) {
            handleLoop(subLoop, LAM, LSAR);
        }
    }
}

PreservedAnalyses AvmusatovPass::run(Function& F, FunctionAnalysisManager& AM) {

    auto& result = AM.getResult<AvmusatovAnalysis>(F);

    totalAddOperationCount += result.addOperationCount;
    totalMulOperationCount += result.mulOperationCount;
    totalPowOperationCount += result.powOperationCount;
    totalBasicBlocksCount += result.basicBlockCount;

    result.printResults(errs());

    auto& LA = AM.getResult<LoopAnalysis>(F);
    auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

    auto& AA = AM.getResult<AAManager>(F);
    AssumptionCache& AC = AM.getResult<AssumptionAnalysis>(F);
    DominatorTree& DT = AM.getResult<DominatorTreeAnalysis>(F);
    ScalarEvolution& SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    TargetLibraryInfo& TLI = AM.getResult<TargetLibraryAnalysis>(F);
    TargetTransformInfo& TTI = AM.getResult<TargetIRAnalysis>(F);
    LoopStandardAnalysisResults LSAR = { AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr };

    for (auto& L : LA)
        handleLoop(L, LAM, LSAR);

    return PreservedAnalyses::all();
}