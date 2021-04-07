#include "llvm/Analysis/AKomyaginAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

namespace llvm {

	AnalysisKey AKomyaginAnalysis::Key;

	AKomyaginAnalysis::Result AKomyaginAnalysis::run(Function& F, FunctionAnalysisManager& FAM) {
		Result result;

		for (Function::iterator iter1 = F.begin(); iter1 != F.end(); ++iter1) 
		{
			for (BasicBlock::iterator iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2) 
			{
				if (std::string(iter2->getOpcodeName()) == "add" || std::string(iter2->getOpcodeName()) == "fadd")
					result.totalAdd++;
				if (std::string(iter2->getOpcodeName()) == "mul" || std::string(iter2->getOpcodeName()) == "fmul")
                    result.totalMul++;
			}
		}

		for (auto& I : instructions(F)) 
		{
			if (auto C = dyn_cast<CallInst>(&I))
				if (C->getCalledFunction()->getName() == "powf")
					result.totalPow++;
		}
		return result;
	}

	void AKomyaginAnalysisInfo::print(raw_ostream &OS)
	{
        OS << "pows: " << totalPow << "\n";
        OS << "adds: " << totalAdd << "\n";
		OS << "muls: " << totalMul << "\n";
	}
}