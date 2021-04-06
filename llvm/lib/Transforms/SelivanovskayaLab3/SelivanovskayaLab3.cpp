#include "llvm/Transforms/SelivanovskayaLab3/SelivanovskayaLab3.h"
#include "llvm/Analysis/SelivanovskayaAnalysis.h"
#include "llvm/Analysis/SelivanovskayaLoopAnalysis.h"

#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"

#define DEBUG_TYPE "SelivanovskayaLab3"
using namespace llvm;

STATISTIC(VecLoops, "Number of vectorizable loops");
STATISTIC(Adds, "Adds num");
STATISTIC(Muls, "Muls num");
STATISTIC(Pows, "Pows num");


void VecLoopsCnt(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {

    if (L->isInnermost()) {
        auto& result = LAM.getResult<SelivanovskayaLoopAnalysis>(*L, LSAR);
        if (result.updatesCnt == 1) {
            VecLoops++;
        }                                                                                                  
    }
    else {
        for (Loop* sloop : L->getSubLoops()) {
        VecLoopsCnt(sloop, LAM, LSAR);
        }
    }

}

PreservedAnalyses SelivanovskayaLab3::run(Function &F, FunctionAnalysisManager &AM) {

    auto& result = AM.getResult<SelivanovskayaAnalysis>(F);
    Adds += result.Adds;
    Muls += result.Muls;
    Pows += result.Pows;
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
        VecLoopsCnt(loop, LAM, LSAR);

    return PreservedAnalyses::all();
} 
