#include "llvm/Analysis/DVorobyovLoopAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"


using namespace llvm;
AnalysisKey DVorobyovLoopAnalysis::Key;

DVorobyovLoopAnalysis::Result DVorobyovLoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LAS)
{
	Result result;
	if (PHINode* indVar = L.getCanonicalInductionVariable())
	{
		SmallVector<BinaryOperator*, 16> updates;
		for (uint32_t i = 0; i < indVar->getNumIncomingValues(); ++i)
		{
			if (auto* binaryOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i)))
			{
				if (binaryOp->getOperand(0) == indVar || binaryOp->getOperand(1) == indVar)
					updates.push_back(binaryOp);
			}
		}
		result.updates_counter = updates.size();
	}
	return result;
}