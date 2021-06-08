#include "llvm/Analysis/udachinaAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"


using namespace llvm;

AnalysisKey udachinaAnalysis::Key;



udachinaAnalysis::Result udachinaAnalysis::run(Function& F, FunctionAnalysisManager& AM){

	Result data;

	for (Function::iterator B = F.begin(); B != F.end(); ++B)
	{
		for (BasicBlock::iterator H = B->begin(); H != B->end(); ++H)
		{
			if (std::string(H->getOpcodeName()) == "mul" || std::string(H->getOpcodeName()) == "fmul")
			{
				data.val_mul++;
			};

			if (std::string(H->getOpcodeName()) == "add" || std::string(H->getOpcodeName()) == "fadd")
			{
				data.val_add++;
			};


		}
	}

	for (Instruction &I : instructions(F))
		if (CallInst *C = dyn_cast<CallInst>(&I))
			if (C->getCalledFunction()->getName() == "powf")
			{
				data.val_block++;
			};

	return data;
}

void udachinaAnalysisInfo::print(raw_ostream &ostream)const {

	ostream << "Add: " << val_add << "/n";
	ostream << "Mul: " << val_mul << "/n";
	ostream << "Block: " << val_block << "/n";


}