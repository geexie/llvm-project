#include "llvm/Transforms/FoLgACount/FoLgACount.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

#define DEBUG_TYPE "of-count"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(Fun_Count, "Amount of functions");
ALWAYS_ENABLED_STATISTIC(Op_Count, "Amount of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(BB_Count, "Amount of BasicBlocks");
ALWAYS_ENABLED_STATISTIC(Loop_Count, "Amount of Loops");

PreservedAnalyses FoLgACountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

  Fun_Count += 1;
  auto& LA = AM.getResult<LoopAnalysis>(F);
  for (auto& L : LA) {
    Loop_Count += 1;
  }
  for (const BasicBlock &BB : F) {
    BB_Count += 1;
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
        Op_Count += 1;
        break;
      }
    }
  }
  errs() << " Amount of arithmetic operations " << Op_Count << "\n";
  errs() << " Amount of functions " << Fun_Count << "\n";
  errs() << " Amount of basic blocks " << BB_Count << "\n";
  errs() << " Amount of loops " << Loop_Count << "\n";
  return PreservedAnalyses::all();
} 