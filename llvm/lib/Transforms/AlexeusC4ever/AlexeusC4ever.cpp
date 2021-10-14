#include "llvm/Transforms/AlexeusC4ever/AlexeusC4ever.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Instructions.h"

#define DEBUG_TYPE "AlexeusC4ever_count"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(NUM_FUNCTIONS, "Number of functions");
ALWAYS_ENABLED_STATISTIC(NUM_ARITHMETIC_OPERATIONS,
                         "Number of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(NUM_BASICBLOCKS, "Number of BasicBlocks");
ALWAYS_ENABLED_STATISTIC(NUM_LOOPS, "Number of loops");

PreservedAnalyses AlexeusC4everPass::run(Function &F,
                                          FunctionAnalysisManager &AM) {

  NUM_FUNCTIONS += 1;

  auto &LA = AM.getResult<LoopAnalysis>(F);

  NUM_LOOPS += LA.end() - LA.begin();

  for (const BasicBlock &BB : F) {
    NUM_BASICBLOCKS += 1;
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
        NUM_ARITHMETIC_OPERATIONS += 1;
        break;
      }
    }
  }

  return PreservedAnalyses::all();
}