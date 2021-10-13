#include "llvm/Transforms/GNCount/GNCount.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

#define DEBUG_TYPE "gn-count"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(FunCount, "Number of functions");
ALWAYS_ENABLED_STATISTIC(OpCount, "Number of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(BBCount, "Number of BasicBlocks");
ALWAYS_ENABLED_STATISTIC(LoopCount, "Number of Loops");

PreservedAnalyses GNCountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  
  FunCount += 1;
  auto& LA = AM.getResult<LoopAnalysis>(F);
  for (auto& L : LA) {
    LoopCount += 1;
  }
  for (const BasicBlock &BB : F) {
    BBCount += 1;
    for (const Instruction &I : BB) {
      switch (I.getOpcode()) {
      case Instruction::Add:
      case Instruction::Sub:
      case Instruction::Mul:
      case Instruction::FAdd:
      case Instruction::FSub:
      case Instruction::FMul:
      case Instruction::FDiv:
      case Instruction::SDiv:
      case Instruction::UDiv:
        OpCount += 1;
        break;
      }
    }
  }
  errs() << " Number of arithmetic operations " << OpCount << "\n";
  errs() << " Number of functions " << FunCount << "\n";
  errs() << " Number of basic blocks " << BBCount << "\n";
  errs() << " Number of loops " << LoopCount << "\n";
  return PreservedAnalyses::all();
}