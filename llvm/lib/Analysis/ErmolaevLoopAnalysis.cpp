#include "llvm/Analysis/ErmolaevLoopAnalysis.h"

#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

AnalysisKey ErmolaevLoopAnalysis::Key;
ErmolaevLoopAnalysis::Result ErmolaevLoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) 
{
    Result result;

    if(PHINode* IV = L.getCanonicalInductionVariable()) 
    {
        SmallVector<BinaryOperator*, 16> updates;
        for (unsigned int i = 0; i < IV->getNumIncomingValues(); i++) 
        {
            if (auto* BO = dyn_cast<BinaryOperator>(IV->getIncomingValue(i))) 
            {
                if (BO->getOperand(0) == IV || BO->getOperand(1) == IV){
                    updates.push_back(BO);
				}
            }
        }
        result.updates = updates.size();
    }
    return result;
} 