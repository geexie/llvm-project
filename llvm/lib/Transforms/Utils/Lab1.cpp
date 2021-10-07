#include "llvm/Transforms/Utils/Lab1.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Instructions.h"

#define DEBUG_TYPE "Lab1"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(NumFunctions, "Number of functions");
ALWAYS_ENABLED_STATISTIC(NumArithmeticOPS, "Number of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(NumBB, "Number of BasicBlocks");

PreservedAnalyses Lab1Pass::run(Function &F, FunctionAnalysisManager &AM) {

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

  return PreservedAnalyses::all();
}
