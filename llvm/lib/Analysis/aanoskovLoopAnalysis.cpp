#include "llvm/Analysis/aanoskovLoopAnalysis.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

AnalysisKey aanoskovLoopAnalysis::Key;

aanoskovLoopAnalysis::Result aanoskovLoopAnalysis::run(Loop &L, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LSAR){
    Result res;
        if(PHINode* indVar = L.getCanonicalInductionVariable())
        {
            SmallVector<BinaryOperator*, 16> updates;
            for (unsigned int i = 0; i < indVar->getNumIncomingValues(); ++i)
            {
                if (auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i)))
                {
                    if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar)
                    {
                        updates.push_back(binOp);
                    }
                }
            }
            res.InvUpdatesCount = updates.size();
        }   
    return res;
}
