#include "llvm\Transforms\KMLab1Pass\KMLab1Pass.h"

#define DEBUG_TYPE "KMLab1Pass" 

using namespace llvm;

STATISTIC(CountDefinitions, "Number of definitions");
STATISTIC(CountLoops, "Number of loops");
STATISTIC(CountBlocks, "Number of basic blocks");
STATISTIC(CountAdd, "Number of add instructions");
STATISTIC(CountMul, "Number of mull instructions");

void LoopCounter(Loop *L) {
  CountLoops++;
  for (auto loop = L->begin(); loop != L->end(); ++loop) {
    LoopCounter(*loop);
  }
  return;
}

PreservedAnalyses KMLab1Pass::run(Function& func, FunctionAnalysisManager& AM) {
	

	if (!func.isDeclaration()) {
		CountDefinitions++;

	llvm::LoopAnalysis::Result &L = AM.getResult<LoopAnalysis>(func);
                for (auto loop = L.begin(); loop != L.end(); ++loop) {
                  LoopCounter(*loop);
                }

		for (Function::iterator bb = func.begin(); bb != func.end();++bb) { 
			CountBlocks++;
			for (BasicBlock::iterator instr = bb->begin(); instr != bb->end(); ++instr) {  
				if (std::string(instr.getOpcodeName()) == "mul" || std::string(instr.getOpcodeName()) == "fmul") {
                ++CountMul;
            }
				else if (std::string(instr.getOpcodeName()) == "add" || std::string(instr.getOpcodeName()) == "fadd") {
                ++CountAdd;
            }
			}
		}
	}
	return PreservedAnalyses::all();
}