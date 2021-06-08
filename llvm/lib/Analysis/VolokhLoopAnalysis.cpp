#include "llvm/Analysis/VolokhLoopAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

namespace llvm {

    AnalysisKey VolokhLoopAnalysis::Key;

    VolokhLoopAnalysis::Result VolokhLoopAnalysis::run(Loop& loop, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LAS){
        Result res;
        if (PHINode* indVar = loop.getCanonicalInductionVariable()){
            SmallVector<BinaryOperator*, 16> upds;
            for (uint32_t i = 0; i < indVar->getNumIncomingValues(); ++i){
                if (auto* binaryOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))){
                    if (binaryOp->getOperand(0) == indVar || binaryOp->getOperand(1) == indVar)
                        upds.push_back(binaryOp);
                }
            }
            res.updates = upds.size();
        }
        return res;
    }
}