#include "llvm/Analysis/MelnikovLab3LoopAnalysis.h"
#include "llvm/IR/Instructions.h"

#include <set>


using namespace llvm;

AnalysisKey MelnikovLab3LoopAnalysis::Key;

MelnikovLab3LoopAnalysis::Result MelnikovLab3LoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR){

    MelnikovLab3LoopAnalysisInfo LAI;

    if (PHINode* indVar = L.getCanonicalInductionVariable()) {
        SmallVector<BinaryOperator*, 16> updates;
        for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
            if (auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))){
                if(binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar){
                    updates.push_back(binOp);
                }
            }
        }
        LAI.IVUpdatesCount = updates.size();
    }
    return LAI;
}