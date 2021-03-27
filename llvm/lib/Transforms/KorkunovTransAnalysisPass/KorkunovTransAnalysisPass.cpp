
#include "llvm/Transforms/KorkunovTransAnalysisPass/KorkunovTransAnalysisPass.h"

#include "llvm/Analysis/KorkunovAnalysisPass.h"
#include "llvm/Analysis/KorkunovLoopAnalysis.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"

#define DEBUG_TYPE "KorkunovTransAnalysisPass"
#include "llvm/ADT/Statistic.h"

STATISTIC(TotalfMul,  "Number of fmull");
STATISTIC(TotalfAdd,  "Number of fadd");
STATISTIC(TotalPowf,  "Number of powf");

STATISTIC(TotalVectorizableLoops,  "Number of vec. Lops");

using namespace llvm;

void KorkunovTransAnalysisPass::iterateOnLoops(llvm::Loop &L, llvm::LoopAnalysisManager &LAM, llvm::LoopStandardAnalysisResults &LSAR){
    if(L.isInnermost()){
        auto KLA = LAM.getResult<KorkunovLoopAnalysis>(L, LSAR);
        if(KLA.InvUpdatesCount == 1)
            TotalVectorizableLoops++;
    }

    for(auto& SL: L.getSubLoops()){
        iterateOnLoops(*SL, LAM, LSAR);
    }
}

PreservedAnalyses KorkunovTransAnalysisPass::run(Function &F, FunctionAnalysisManager &AM){
    auto& FP = AM.getResult<KorkunovAnalysisPass>(F);
   // FP.print(errs());
    TotalfMul+=FP.tfmul;
    TotalfAdd+=FP.tfadd;
    TotalPowf+=FP.tpowf;


    auto& LI = AM.getResult<LoopAnalysis>(F);
    auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

    auto& AA = AM.getResult<AAManager>(F);
    auto& AC = AM.getResult<AssumptionAnalysis>(F);
    auto& DT = AM.getResult<DominatorTreeAnalysis>(F);
    auto& SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    auto& TLI = AM.getResult<TargetLibraryAnalysis>(F);
    auto& TTI = AM.getResult<TargetIRAnalysis>(F);
    LoopStandardAnalysisResults AR = {AA, AC, DT, LI, SE, TLI, TTI, nullptr, nullptr};
    for(auto& L : LI){
        iterateOnLoops(*L, LAM, AR); ///wp
    }

    auto pa = PreservedAnalyses::all();
    return pa;
}