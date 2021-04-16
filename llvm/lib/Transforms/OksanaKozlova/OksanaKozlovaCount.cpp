#include "llvm/Transforms/OksanaKozlova/OksanaKozlovaCount.h"
#include "llvm/Analysis/OksanaKozlovaAnalysis.h"
#include "llvm/Analysis/OksanaKozlovaLoopAnalysis.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

#define DEBUG_TYPE "oksana-count"
using namespace llvm;

STATISTIC(TotalFuncs, "Number of functions");
STATISTIC(TotalBasicBlocks, "Number of basic blocks");
STATISTIC(TotalArithmInstrs, "Number of arithmetic instructions");
STATISTIC(TotalLoopsVertorizable, "Number of vectorizable loops");


static void handleLoops(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& AR) {
    if (L->isInnermost()) {
        auto &result = LAM.getResult<OksanaKozlovaLoopAnalysis>(*L, AR);
        if (result.updCount == 1) {
            TotalLoopsVertorizable++;
        }
    }

    for (Loop* SL : L->getSubLoops()) {
        handleLoops(SL, LAM, AR);
    }

}

PreservedAnalyses OksanaKozlovaCountPass::run(Function &F, FunctionAnalysisManager &AM) {

    auto &result = AM.getResult<OksanaKozlovaAnalysis>(F);

    TotalFuncs += result.totalFuncs;
    TotalBasicBlocks += result.totalBasicBlocks;
    TotalArithmInstrs += result.totalArithmInstrs;

    auto& LA = AM.getResult<LoopAnalysis>(F);
    auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

    auto& AA = AM.getResult<AAManager>(F);
    AssumptionCache &AC = AM.getResult<AssumptionAnalysis>(F);
    DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
    ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    TargetLibraryInfo &TLI = AM.getResult<TargetLibraryAnalysis>(F);
    TargetTransformInfo &TTI = AM.getResult<TargetIRAnalysis>(F);

    LoopStandardAnalysisResults AR = {AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr};

    for (auto& L : LA)
        handleLoops(L, LAM, AR);

    return PreservedAnalyses::all();
}