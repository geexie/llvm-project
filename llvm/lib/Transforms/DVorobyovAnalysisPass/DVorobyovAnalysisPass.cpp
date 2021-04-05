#pragma once

#include "llvm/Transforms/DVorobyovAnalysisPass/DVorobyovAnalysisPass.h"
#include "llvm/Analysis/DVorobyovAnalysis.h"
#include "llvm/Analysis/DVorobyovLoopAnalysis.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"

#define DEBUG_TYPE "DVorobyovAnalysisPass"


STATISTIC(Adds_counter, "Adds");
STATISTIC(Muls_counter, "Muls");
STATISTIC(Powfs_counter, "Powfs");
STATISTIC(Loops_counter, "Loops");


using namespace llvm;


void Loops(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR)
{
    if (L->isInnermost())
	{
        auto& result = LAM.getResult<DVorobyovhLoopAnalysis>(*L, LSAR);
        if (result.updates_counter == 1)
            Loops_counter++;
    }
    for (Loop* loop : L->getSubLoops())
        Loops(loop, LAM, LSAR);
}


PreservedAnalyses DVorobyovAnalysisPass::run(Function& F, FunctionAnalysisManager& FAM)
{
    auto& result = FAM.getResult<DVorobyovAnalysis>(F);
    Adds_counter += result.adds;
    Muls_counter += result.muls;
    Powfs_counter += result.powfs;

    result.print(errs());

    auto& LA = FAM.getResult<LoopAnalysis>(F);
    auto& LAM = FAM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

    auto& AA = FAM.getResult<AAManager>(F);
    auto& AC = FAM.getResult<AssumptionAnalysis>(F);
    auto& DT = FAM.getResult<DominatorTreeAnalysis>(F);
    auto& SE = FAM.getResult<ScalarEvolutionAnalysis>(F);
    auto& TLI = FAM.getResult<TargetLibraryAnalysis>(F);
    auto& TTI = FAM.getResult<TargetIRAnalysis>(F);
    LoopStandardAnalysisResults AR = {AA, AC, DT, LA, SE, TLI, TTI, nullptr, nullptr};
    for(auto& L : LA)
	{
        Loops(L, LAM, AR);
    }
    return PreservedAnalyses::all();
}