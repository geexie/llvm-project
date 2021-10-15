#include "llvm/Transforms/TimurZaytsev/TimurZaytsev.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

#define DEBUG_TYPE "TimurZaytsev"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(Fun_Count, "Amount of functions");
ALWAYS_ENABLED_STATISTIC(Op_Count, "Amount of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(B_Count, "Amount of blocks");
ALWAYS_ENABLED_STATISTIC(Loop_Count, "Amount of loops");

PreservedAnalyses TimurZaytsevPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

  Fun_Count++;
  auto& LA = AM.getResult<LoopAnalysis>(F);
  for (auto& L : LA) {
    Loop_Count++;
  }
  for (const BasicBlock &BB : F) {
    B_Count++;
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
        Op_Count++;
        break;
      }
    }
  }
  errs() << " Amount of arithmetic operations " << Op_Count << "\n";
  errs() << " Amount of loops " << Loop_Count << "\n";
  errs() << " Amount of functions " << Fun_Count << "\n";
  errs() << " Amount of blocks " << B_Count << "\n";
  return PreservedAnalyses::all();
} 