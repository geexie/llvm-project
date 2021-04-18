#include "llvm/Analysis/PankratovaLoopAnalysis.h"

using namespace llvm;
AnalysisKey PankratovaLoopAnalysis::Key;


PankratovaLoopAnalysis::Result PankratovaLoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
    Result result;

    if(PHINode* indVar = L.getCanonicalInductionVariable()) {
        SmallVector<BinaryOperator*, 16> updates;
        for (size_t i = 0; i < indVar->getNumIncomingValues(); i++) {
            if (auto* BO = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
                if (BO->getOperand(0) == indVar || BO->getOperand(1) == indVar) {
                    updates.push_back(BO);
                }
            }
        }
        result.count = updates.size();
    }
    return result;
}
