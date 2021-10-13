#include <string>

#include "llvm/Transforms/NikitaCount/NikitaCount.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

#define DEBUG_TYPE "NikitaCount"

ALWAYS_ENABLED_STATISTIC(func_counter, "Function counter");
ALWAYS_ENABLED_STATISTIC(block_counter, "Block counter");
ALWAYS_ENABLED_STATISTIC(instr_counter, "Arithmetic operation counter");
ALWAYS_ENABLED_STATISTIC(loop_counter, "Loop counter");

PreservedAnalyses NikitaCountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  ++func_counter;
  for (auto BB = F.begin(); BB != F.end(); ++BB) {
      ++block_counter;
      for (auto I = BB->begin(); I != BB->end(); ++I) {
          switch (I->getOpcode()) {
            case Instruction::Add:
            case Instruction::FAdd:
            case Instruction::Sub:
            case Instruction::FSub:
            case Instruction::Mul:
            case Instruction::FMul:
            case Instruction::FDiv:
            case Instruction::SDiv:
            case Instruction::UDiv:
                ++instr_counter;
        }
      }
  }
  auto& LA = AM.getResult<LoopAnalysis>(F);
  for (auto& L : LA) {
      errs() << "loop: " << L->getName() << "\n";
      ++loop_counter;
  }
  errs() << "Func: " << func_counter << "\n";
  errs() << "Block: " << block_counter << "\n";
  errs() << "Arithmetic operations: " << instr_counter << "\n";
  errs() << "Loop: " << loop_counter << "\n";
  errs() << "================================\n\n";
  return PreservedAnalyses::all();
}