#include "llvm/Analysis/VoronovaAnalisis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

namespace llvm {

	AnalysisKey VoronovaAnalisis::Key;

	VoronovaAnalisis::Result VoronovaAnalisis::run(Function& F, FunctionAnalysisManager& FAM) {
		Result result;

		for (Function::iterator i = F.begin(); i != F.end(); ++i) 
		{
			for (BasicBlock::iterator j = i->begin(); j != i->end(); ++j) 
			{
				if (std::string(j->getOpcodeName()) == "add" || std::string(j->getOpcodeName()) == "fadd")
					result.CountAdds++;
				if (std::string(j->getOpcodeName()) == "mul" || std::string(j->getOpcodeName()) == "fmul")
                    result.CountMulls++;
			}
		}

		for (auto& I : instructions(F)) 
		{
			if (auto C = dyn_cast<CallInst>(&I))
				if (C->getCalledFunction()->getName() == "powf")
					result.CountPows++;
		}
		return result;
	}

	void VoronovaAnalisisInfo::output(raw_ostream& OS) 
	{
        OS << "pows: " << CountPows << "\n";
        OS << "adds: " << CountAdds << "\n";
		OS << "muls: " << CountMulls << "\n";
	}

}