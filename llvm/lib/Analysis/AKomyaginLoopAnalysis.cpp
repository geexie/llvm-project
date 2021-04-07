#include "llvm/Analysis/AKomyaginLoopAnalysis.h"

#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

namespace llvm{

    AnalysisKey AKomyaginLoopAnalysis::Key;

    AKomyaginLoopAnalysis::Result AKomyaginLoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA) {
        Result result;

        if(PHINode* indVar = L.getCanonicalInductionVariable()) {
            SmallVector<BinaryOperator*, 16> updates;
            for (uint32_t i = 0; i < indVar->getNumIncomingValues(); ++i) {
                if (auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
                    if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar) {
                        updates.push_back(binOp);
                    }
                }
            }
            result.InvUpd = updates.size();
        }

        return result;
    } 
}