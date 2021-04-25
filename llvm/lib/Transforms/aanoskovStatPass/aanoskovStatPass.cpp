#include "llvm/Transforms/aanoskovStatPass/aanoskovStatPass.h"
#include "llvm/Analysis/aanoskovCounter.h"
#include "llvm/Analysis/aanoskovLoopAnalysis.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/DomTreeUpdater.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

using namespace llvm;

#define DEBUG_TYPE "aanoskovStatPass"

STATISTIC(TotalFuncDefs, "Number of function definitions");
STATISTIC(TotalBasicBlocks, "Number of basic blocks");
STATISTIC(TotalAdds, "Number of Adds");
STATISTIC(TotalMuls, "Number of Muls");
STATISTIC(TotalVectLoops, "Number of loops");


void LoopsRecursion(Loop* loop, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LSAR)
{
    if (loop->isInnermost())
    {
        auto& L = LAM.getResult<aanoskovLoopAnalysis>(*loop, LSAR);
        if(L.InvUpdatesCount == 1)
            ++TotalVectLoops;
    }
    else
    {
        for(Loop::iterator innerLoop = loop->begin(); innerLoop != loop->end(); ++innerLoop)
        {
            LoopsRecursion(*innerLoop, LAM, LSAR);
        }
    }
}


PreservedAnalyses aanoskovStatPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
    errs() << F.getName() << "\n";
    if (!F.isDeclaration())
        TotalFuncDefs++;

    auto& FPI = AM.getResult<aanoskovCounterAnalysis>(F);
    TotalBasicBlocks += FPI.BasicBlockCount;
    TotalAdds += FPI.AddsCount;
    TotalMuls += FPI.MulsCount;

    FPI.print(errs());
    auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();
    auto& LA  = AM.getResult<LoopAnalysis>(F);

    auto& AA = AM.getResult<AAManager>(F);
    AssumptionCache &AC = AM.getResult<AssumptionAnalysis>(F);
    // for  for
    DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
    // int sum = 0;
    // for (int i = 0; i < 100; i++) {
    //  sum += ptr[i];
    //}
    // int avg = sum / 100;
    ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    TargetLibraryInfo &TLI = AM.getResult<TargetLibraryAnalysis>(F);
    TargetTransformInfo &TTI = AM.getResult<TargetIRAnalysis>(F);

    LoopStandardAnalysisResults LSAR = {AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr};

    for(LoopInfo::iterator loop = LA.begin(); loop != LA.end(); ++loop)
    {
        LoopsRecursion(*loop, LAM, LSAR);
    }

    return PreservedAnalyses::all();
}
