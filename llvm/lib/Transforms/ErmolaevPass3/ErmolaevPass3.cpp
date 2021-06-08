#include "llvm/Transforms/ErmolaevPass3/ErmolaevPass3.h"
#include "llvm/Analysis/ErmolaevAnalysis.h"
#include "llvm/Analysis/ErmolaevLoopAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

#define DEBUG_TYPE "ErmolaevPass3"

using namespace llvm;

STATISTIC(Total_add, "Number of adds");
STATISTIC(Total_mul, "Number of muls");
STATISTIC(Total_pow, "Number of pows");
STATISTIC(Total_Vec_Loops, "Number of vectorizable loops");


void countTotal_Vec_Loops(Loop* loop, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    if (loop->isInnermost()) {
        auto& result = LAM.getResult<ErmolaevLoopAnalysis>(*loop, LSAR);
        if (result.updates == 1){
            Total_Vec_Loops++;    
		}			
    }
    else {
        for (Loop* loop : loop->getSubLoops()){
            countTotal_Vec_Loops(loop, LAM, LSAR);
		}
    }
}

PreservedAnalyses ErmolaevPass3::run(Function &F, FunctionAnalysisManager &AM) {

    auto& result = AM.getResult<ErmolaevAnalysis>(F);
    Total_add += result.addNum;
    Total_mul += result.mulNum;
    Total_pow += result.powNum;

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
        countTotal_Vec_Loops(loop, LAM, LSAR);

    return PreservedAnalyses::all();
} 