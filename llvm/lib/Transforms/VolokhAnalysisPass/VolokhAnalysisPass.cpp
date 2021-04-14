#pragma once

#include "llvm/Transforms/VolokhAnalysisPass/VolokhAnalysisPass.h"
#include "llvm/Analysis/VolokhAnalysis.h"
#include "llvm/Analysis/VolokhLoopAnalysis.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"

#define DEBUG_TYPE "VolokhAnalysisPass"

STATISTIC(TotalAdds, "Num of adds");
STATISTIC(TotalMuls, "Num of muls");
STATISTIC(TotalPowfs, "Num of powfs");
STATISTIC(TotalVecLoops, "Num of vec loops");

using namespace llvm;

void innLoops(Loop* loop, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LAS){
    if (loop->isInnermost()){
        auto& VLA = LAM.getResult<VolokhLoopAnalysis>(*loop, LAS);
        if (VLA.updates == 1)
            TotalVecLoops++;
    }
    for (Loop* subLoop : loop->getSubLoops())
        innLoops(subLoop, LAM, LAS);
}

PreservedAnalyses VolokhAnalysisPass::run(Function& func, FunctionAnalysisManager& AM){
    auto& VAP = AM.getResult<VolokhAnalysis>(func);
    TotalAdds += VAP.adds;
    TotalMuls += VAP.muls;
    TotalPowfs += VAP.powfs;

    VAP.print(errs());

    auto& LI = AM.getResult<LoopAnalysis>(func);
    auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(func).getManager();

    auto& AA = AM.getResult<AAManager>(func);
    auto& AC = AM.getResult<AssumptionAnalysis>(func);
    auto& DT = AM.getResult<DominatorTreeAnalysis>(func);
    auto& SE = AM.getResult<ScalarEvolutionAnalysis>(func);
    auto& TLI = AM.getResult<TargetLibraryAnalysis>(func);
    auto& TTI = AM.getResult<TargetIRAnalysis>(func);
    LoopStandardAnalysisResults AR = {AA, AC, DT, LI, SE, TLI, TTI, nullptr, nullptr};
    for(auto& L : LI){
        innLoops(L, LAM, AR);
    }
    return PreservedAnalyses::all();
}