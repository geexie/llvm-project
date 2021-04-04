#include "llvm/Transforms/MoiseevPass3>/MoiseevPass3.h"
#include "llvm/Analysis/MoiseevAnalysis.h"
#include "llvm/Analysis/MoiseevLoopAnalysis.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

using namespace llvm;

STATISTIC(TotalAdd, "Number of adds");
STATISTIC(TotalMul, "Number of muls");
STATISTIC(TotalPow, "Number of pows");
STATISTIC(VectorizableLoops, "Number of vectorizable loops");


void countVectorizableLoops(Loop* loop, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    if (loop->isInnermost()) {
        auto& result = LAM.getResult<MoiseevLoopAnalysis>(*loop, LSAR);
        if (result.updates == 1)
            VectorizableLoops++;                                                                                                
    }
    else {
        for (Loop* loop : loop->getSubLoops())
            VectorizableLoops(loop, LAM, LSAR);
    }
}

PreservedAnalyses MoiseevPass3::run(Function &F, FunctionAnalysisManager &AM) {

    auto& result = AM.getResult<MoiseevAnalysis>(F);
    TotalAdd += result.add_num;
    TotalMul += result.mul_num;
    TotalPow += result.pow_num;

    result.print(errs());

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
        VectorizableLoops(loop, LAM, LSAR);

    return PreservedAnalyses::all();
} 