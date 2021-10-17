#include "llvm/Transforms/SlavokeruCount/SlavokeruCount.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

#define DEBUG_TYPE "SlavokeruCount"

ALWAYS_ENABLED_STATISTIC(Fcount, "Num of functions");
ALWAYS_ENABLED_STATISTIC(Bcount, "Num of blocks");
ALWAYS_ENABLED_STATISTIC(Icount, "Num of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(Lcount, "Num of loops");

PreservedAnalyses SlavokeruCountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

  auto& LA = AM.getResult<LoopAnalysis>(F);
  for (auto& loop : LA) {
      errs() << "loop: " << loop->getName() << "\n";
      Lcount++;
  }
  for (auto BB = F.begin(); BB != F.end(); ++BB) {
      Bcount++;
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
                Icount++;
        }
      }
  }
  Fcount++;
  errs() << "Num of funtions: " << Fcount << "\n";
  errs() << "Num of blocks: " << Bcount << "\n";
  errs() << "Num of arithmetic operations: " << Icount << "\n";
  errs() << "Num of loops: " << Lcount << "\n";
  return PreservedAnalyses::all();
}