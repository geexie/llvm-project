#include "llvm/Transforms/ZagoskinVA/GeexieCount.h"
#define DEBUG_TYPE "geexie-count"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
using namespace llvm;

ALWAYS_ENABLED_STATISTIC(NumFunctions, "Number of functions");
ALWAYS_ENABLED_STATISTIC(NumArithmeticOPS, "Number of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(NumBB, "Number of BasicBlocks");
ALWAYS_ENABLED_STATISTIC(LoopsCount, "Number of loops");

PreservedAnalyses GeexieCountPass::run(Function &F, FunctionAnalysisManager &AM){
	  NumFunctions += 1;

	for (const BasicBlock &BB : F) {
		NumBB += 1;
		for (const Instruction &I : BB) {
		switch (I.getOpcode()) {
		case Instruction::Add:
		case Instruction::FAdd:
		case Instruction::Mul:
		case Instruction::FDiv:
		case Instruction::SDiv:
		case Instruction::UDiv:
		case Instruction::Sub:
		case Instruction::FSub:
			NumArithmeticOPS += 1;
			break;
		}
		}
	}

	    auto& LA = AM.getResult<LoopAnalysis>(F);
    for (auto& L : LA) ++LoopsCount;
	  errs() << "Number of functions " << NumFunctions << "\n";
  	errs() << "Number of arithmetic operations " << NumArithmeticOPS << "\n";
  	errs() << "Number of BB " << NumBB << "\n";
	return PreservedAnalyses::all();
}