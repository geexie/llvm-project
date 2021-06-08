#include "llvm/Analysis/SelivanovskayaLoopAnalysis.h"

using namespace llvm;

AnalysisKey SelivanovskayaLoopAnalysis::Key;

SelivanovskayaLoopAnalysis::Result SelivanovskayaLoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {

    Result result;

    if(PHINode* indVar = L.getCanonicalInductionVariable()) {
        SmallVector<BinaryOperator*, 16> upds;
        for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
            if (auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
                if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar) {
                    upds.push_back(binOp);
                }
            }
        }
        result.updatesCnt = upds.size();
    }
    
    return result;
} 