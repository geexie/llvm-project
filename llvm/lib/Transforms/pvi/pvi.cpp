#include "llvm/Transforms/pvi/pvi.h"

using namespace llvm;

#define DEBUG_TYPE "pvi"

STATISTIC(FuncsCounter, "Number of functions");
STATISTIC(LoopsCounter, "Number of loops");
STATISTIC(BasicBlockCounter, "Number of basic blocks");
STATISTIC(AddCounter, "Number of +");
STATISTIC(MulCounter, "Number of *");

void countLoops(Loop* loop) {
    LoopsCounter++;
    for (Loop::iterator it = loop->begin(); it != loop->end(); ++it){
        countLoops(*it);
	}
}

PreservedAnalyses pvi::run(Function &F, FunctionAnalysisManager &AM) {
	if (!F.isDeclaration()) {
		FuncsCounter++;

		llvm::LoopAnalysis::Result& loops = AM.getResult<LoopAnalysis>(F);
		for (Loop::iterator loop_it = loops.begin(); loop_it != loops.end(); ++loop_it){
			countLoops(*loop_it);
		}


		for (Function::iterator bb_it = F.begin(); bb_it != F.end(); ++bb_it) {
			BasicBlockCounter++;

			for (BasicBlock::iterator instr_it = bb_it->begin(); instr_it != bb_it->end(); ++instr_it)
			{
				if (std::string(instr_it->getOpcodeName()) == "add" || std::string(instr_it->getOpcodeName()) == "fadd") 
					AddCounter++;
				if (std::string(instr_it->getOpcodeName()) == "mul" || std::string(instr_it->getOpcodeName()) == "fmul")
					MulCounter++;
			}
		}
	}

	return PreservedAnalyses::all();
}