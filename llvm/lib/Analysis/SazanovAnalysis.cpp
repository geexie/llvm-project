#include "llvm/Analysis/SazanovAnalysis.h"


namespace llvm
{
	
AnalysisKey SazanovAnalysis::Key;

SazanovAnalysis::Result SazanovAnalysis::run(Function& F, FunctionAnalysisManager& FAM)
{
	Result result;
	
	for (auto block = F.begin(); block != F.end(); ++block)
	{
		for (auto instruction = block->begin(); instruction != block->end(); ++instruction)
		{
			std::string opcode = std::string(instruction->getOpcodeName());
			if (opcode == "add" || opcode == "fadd")
			{
				++result.numAdds;
			}
			else if (opcode == "mul" || opcode == "fmul")
			{
				++result.numMuls;
			}
			else if (auto callInst = dyn_cast<CallInst>(instruction))
			{
				if (callInst->getCalledFunction()->getName() == "powf")
				{
					++result.numPows;
				}
			}
		}
	}
	
	return result;
}
	
} //namespace llvm