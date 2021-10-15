#include "llvm/Transforms/Bugrov/Bugrov.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

#define DEBUG_TYPE "Bugrov"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(func_Count, "Amount of functions");
ALWAYS_ENABLED_STATISTIC(operations_Count, "Amount of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(bloks_Count, "Amount of blocks");
ALWAYS_ENABLED_STATISTIC(loop_Count, "Amount of loops");

PreservedAnalyses BugrovPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

  func_Count++;
  auto& LA = AM.getResult<LoopAnalysis>(F);
  for (auto& L : LA) {
    loop_Count++;
  }
  for (const BasicBlock &BB : F) {
    bloks_Count++;
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
        operations_Count++;
        break;
      }
    }
  }
  errs() << " Amount of arithmetic operations " << operations_Count << "\n";
  errs() << " Amount of loops " << loop_Count << "\n";
  errs() << " Amount of functions " << func_Count << "\n";
  errs() << " Amount of blocks " << bloks_Count << "\n";
  return PreservedAnalyses::all();
} 