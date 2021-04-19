
#include "llvm/Transforms/Bogoroditskaya3/Bogoroditskaya3.h"
#include "llvm/Analysis/BogoroditskayaFunctionAnalysis.h"
#include "llvm/Analysis/BogoroditskayaLoopAnalysis.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/Dominators.h"

#define DEBUG_TYPE "Bogoroditskaya3"

using namespace llvm;

STATISTIC(TotalLoops, "Number of loops");
STATISTIC(TotalAdd, "Number of Arithmetic instructions of type add");
STATISTIC(TotalMull, "Number of Arithmetic instructions of type mull");

void handleLoops(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& AR) {
    if (L->isInnermost()) {
        auto& GLA = LAM.getResult<BogoroditskayaLoopAnalysis>(*L, AR);
        if (GLA.InvUpdatesCount == 1) {
            ++TotalLoops;
        }
    }
    for (Loop* SL : L->getSubLoops()) {
        handleLoops(SL, LAM, AR);
    }
}

PreservedAnalyses Bogoroditskaya3::run(Function &F, FunctionAnalysisManager &AM) 
{
    auto& GFP = AM.getResult<BogoroditskayaFunctionAnalysis>(F);
    TotalAdd += GFP.Num_Add;
    TotalMull += GFP.Num_Mull;
    TotalLoops += GFP.Num_Pow;

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
        handleLoops(L, LAM, AR);

    return PreservedAnalyses::all();
}

