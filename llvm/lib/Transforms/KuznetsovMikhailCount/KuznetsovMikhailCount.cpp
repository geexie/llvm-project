#include <set>
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Transforms/KuznetsovMikhailCount/KuznetsovMikhailCount.h"


#define DEBUG_TYPE "KuznetsovMikhailCount"

ALWAYS_ENABLED_STATISTIC(funNum, "Number of functions");
ALWAYS_ENABLED_STATISTIC(lpNum, "Number of loops");
ALWAYS_ENABLED_STATISTIC(bbNum, "Number of BB");
ALWAYS_ENABLED_STATISTIC(opsNum, "Number of arithmetic OPS");

llvm::PreservedAnalyses llvm::KuznetsovMikhailCountPass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
  std::set <unsigned int> artmInstr {Instruction::Add, Instruction::FAdd,
                                    Instruction::Sub, Instruction::FSub,
                                    Instruction::Mul, Instruction::SDiv,
                                    Instruction::UDiv, Instruction::FDiv};
  for (auto & bb : F) {
    ++bbNum;
    for (auto & in : bb) {
      auto code = in.getOpcode();
      if (artmInstr.count(code)) {
        ++opsNum;
      }
    }
  }
  ++funNum;
  auto & lpAn = AM.getResult<LoopAnalysis>(F);
  lpNum += lpAn.end() - lpAn.begin();
  errs() << "Number of functions: " << funNum << "\n";
  errs() << "Number of loops: " << lpNum << "\n";
  errs() << "Number of BB: " << bbNum << "\n";
  errs() << "Number of arithmetic OPS: " << opsNum << "\n";
  return PreservedAnalyses::all();
}
