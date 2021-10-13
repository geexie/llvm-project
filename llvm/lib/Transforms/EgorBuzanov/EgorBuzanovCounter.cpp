#include "llvm/Transforms/EgorBuzanov/EgorBuzanovCounter.h"

#define DEBUG_TYPE "EgorBuzanov"

#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(loop_count, "Loop counter");
ALWAYS_ENABLED_STATISTIC(fun_count, "Function counter");
ALWAYS_ENABLED_STATISTIC(block_count, "Block counter");
ALWAYS_ENABLED_STATISTIC(op_count, "Arithmetic operation counter");

llvm::PreservedAnalyses EgorBuzanovCounter::run(Function &F,
                                                FunctionAnalysisManager &AM) {
  ++fun_count;

  const auto &all_loops = AM.getResult<LoopAnalysis>(F);
  for (const auto &loop : all_loops) {
    ++loop_count;
  }

  for (auto &BB : F) {
    for (auto op = BB.begin(); op != BB.end(); ++op) {
      if ((op->getOpcode() == 13) || (op->getOpcode() == 15) ||
          (op->getOpcode() == 17) || (op->getOpcode() == 20) ||
          (op->getOpcode() == 23)) {
        ++op_count;
      }
    }
    ++block_count;
  }

  errs() << "Loops: " << loop_count << "\n";
  errs() << "Functions: " << fun_count << "\n";
  errs() << "Blocks: " << block_count << "\n";
  errs() << "Operations: " << op_count << "\n";
  errs() << "End\n";
  return PreservedAnalyses::all();
}
