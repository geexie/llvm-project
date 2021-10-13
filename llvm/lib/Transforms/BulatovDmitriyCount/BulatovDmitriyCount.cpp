#include <vector>
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Transforms/BulatovDmitriyCount/BulatovDmitriyCount.h"

#define DEBUG_TYPE "BulatovDmitriyCount"

ALWAYS_ENABLED_STATISTIC(opsNum, "Number of arithmetic OPS");
ALWAYS_ENABLED_STATISTIC(bbNum, "Number of BB");
ALWAYS_ENABLED_STATISTIC(funNum, "Number of functions");

PreservedAnalyses llvm::BulatovDmitriyCountPass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
  ++funNum;
  std::vector <Instruction> arithmeticInstructions {Instruction::Add, Instruction::FAdd, Instruction::Sub, Instruction::FSub:,
                            Instruction::Mul, Instruction::SDiv, Instruction::UDiv, Instruction::FDiv};
  for (auto bb : F) {
    ++bbNum;
    for (auto in : bb) {
      for (auto arIn : arithmeticInstructions) {
        if(in == arIn) {
          ++opsNum;
          break;
        }
      }
    }
  }
  errs() << "Number of arithmetic OPS: " << opsNum << "\n";
  errs() << "Number of BB: " << bbNum << "\n";
  errs() << "Number of functions: " << funNum << "\n";
  return PreservedAnalyses::all();
}
