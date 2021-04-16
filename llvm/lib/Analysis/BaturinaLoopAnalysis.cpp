#include "llvm/Analysis/BaturinaLoopAnalysis.h"

using namespace llvm;

AnalysisKey BaturinaLoopAnalysis::Key;

BaturinaLoopAnalysis::Result BaturinaLoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    Result result;

    if(PHINode* indVar = L.getCanonicalInductionVariable()) {
        SmallVector<BinaryOperator*, 16> updates;
        for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
            if (auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
                if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar) {
                    updates.push_back(binOp);
                }
            }
        }
        result.updCnt = updates.size();
    }
    return result;
}