#include "llvm/Transforms/DBarinovCount/DBarinovCount.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Instructions.h"

#define DEBUG_TYPE "DBarinovCount"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(FUNC_NUM, "Number of functions");
ALWAYS_ENABLED_STATISTIC(OP_NUM, "Number of operations");
ALWAYS_ENABLED_STATISTIC(BB_NUM, "Number of basicblocks");
ALWAYS_ENABLED_STATISTIC(LOOP_NUM, "Number of loops");

PreservedAnalyses DBarinovPass::run(Function &F,
                                          FunctionAnalysisManager &AM) {

  FUNC_NUM += 1;
  auto &LA = AM.getResult<LoopAnalysis>(F);
  LOOP_NUM += LA.end() - LA.begin();

  for (const BasicBlock &BB : F) {
    BB_NUM += 1;
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
        OP_NUM += 1;
        break;
      }
    }
  }

  return PreservedAnalyses::all();
}

