#include "llvm/Transforms/VokhmyaninaLab3/VokhmyaninaLab3.h"
#include "llvm/Analysis/VokhmyaninaAnalysis.h"
#include "llvm/Analysis/VokhmyaninaLoopAnalysis.h"

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


void countVecLoops(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    if (L->isInnermost()) {
        auto& res = LAM.getResult<VokhmyaninaLoopAnalysis>(*L, LSAR);
        if (res.updates_count == 1) {
            VectorizableLoops++;
        }                                                                                                  
    }
    else {
        for (Loop* loop : L->getSubLoops()) {
        countVecLoops(loop, LAM, LSAR);
        }
    }
}

PreservedAnalyses VokhmyaninaLab3::run(Function &F, FunctionAnalysisManager &AM) {

    auto& res = AM.getResult<VokhmyaninaAnalysis>(F);
    TotalAdd += res.total_add;
    TotalMul += res.total_mul;
    TotalPow += res.total_pow;

    res.print(errs());

    auto& L = AM.getResult<LoopAnalysis>(F);
    auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

    auto& AA = AM.getResult<AAManager>(F);
    AssumptionCache &AC = AM.getResult<AssumptionAnalysis>(F);
    DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
    ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    TargetLibraryInfo &TLI = AM.getResult<TargetLibraryAnalysis>(F);
    TargetTransformInfo &TTI = AM.getResult<TargetIRAnalysis>(F);
    LoopStandardAnalysisResults LSAR = {AA , AC, DT, L, SE, TLI, TTI, nullptr, nullptr};

    for (auto& loop : L)
        countVecLoops(loop, LAM, LSAR);

    return PreservedAnalyses::all();
} 
