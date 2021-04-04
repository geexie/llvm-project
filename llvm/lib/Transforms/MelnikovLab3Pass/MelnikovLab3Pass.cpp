#include "llvm/Transforms/MelnikovLab3Pass/MelnikovLab3Pass.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"

#include "llvm/Analysis/MelnikovLab3FunctionAnalysis.h"
#include "llvm/Analysis/MelnikovLab3LoopAnalysis.h"

#define DEBUG_TYPE "MelnikovLab3Pass"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

//STATISTIC(TotalDefinitions, "Number of definitions"); 
STATISTIC(TotalBasicBlocks, "Number of basic blocks");
STATISTIC(TotalAdds, "Number of add instructions");
STATISTIC(TotalMulls, "Number of mull instructions");
STATISTIC(TotalLoops, "Number of loops");
STATISTIC(TotalVectorizableLoops, "Number of vectorizable loops");


void check_innermost_loop(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR){
    TotalLoops++;   
    if (L->isInnermost()) {
        auto& LA = LAM.getResult<MelnikovLab3LoopAnalysis>(*L, LSAR);
        if (LA.IVUpdatesCount == 1){ // why the fuck doesn't this shit count
           TotalVectorizableLoops++; 
        }
        errs() << "---IVUpdatesCount: " << LA.IVUpdatesCount << "---\n";
    }

    for (Loop* SL : L->getSubLoops()) {  // iterating over all the loops contained within the current loop
        check_innermost_loop(SL, LAM, LSAR);
    }
}


PreservedAnalyses MelnikovLab3Pass::run(Function& F, FunctionAnalysisManager& AM) {

    auto& FP = AM.getResult<MelnikovLab3FunctionAnalysis>(F);

    TotalBasicBlocks +=  FP.BasicBlockCount;
    TotalAdds += FP.FAddCount;
    TotalMulls += FP.FMullCount;

    auto& LI = AM.getResult<LoopAnalysis>(F);
    auto& LAMFP = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

    auto& AA = AM.getResult<AAManager>(F);
    auto& AC = AM.getResult<AssumptionAnalysis>(F);
    auto& DT= AM.getResult<DominatorTreeAnalysis>(F);
    auto& SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    auto& TLI = AM.getResult<TargetLibraryAnalysis>(F);
    auto& TTI = AM.getResult<TargetIRAnalysis>(F);

    LoopStandardAnalysisResults AR = {AA, AC, DT, LI, SE, TLI, TTI, nullptr, nullptr};
    for (auto& L : LI){
        check_innermost_loop(L, LAMFP, AR);
    }
    return PreservedAnalyses::all();
}
