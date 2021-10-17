#include "llvm/Transforms/KartsevamdCount/KartsevamdCount.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"
#define DEBUG_TYPE "kartsevamd-count"

#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(F_Count, "Functions");
ALWAYS_ENABLED_STATISTIC(O_Count, "Operations");
ALWAYS_ENABLED_STATISTIC(B_Count, "BasicBlocks");
ALWAYS_ENABLED_STATISTIC(L_Count, "Loops");

PreservedAnalyses KartsevamdCountPass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
   F_Count += 1;
  
  for (const BasicBlock &BB : F) {
    B_Count += 1;
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
        O_Count += 1;
        break;
      }
    }
  }
  errs() << " Operations " << O_Count << "\n";
  errs() << " Functions " << F_Count << "\n";
  errs() << " Blocks " << B_Count << "\n";
  errs() << " Loops " << L_Count << "\n";

  auto& LA = AM.getResult<LoopAnalysis>(F);
  for (auto& L : LA) {
    L_Count += 1;
  }
  
  return PreservedAnalyses::all();
} 