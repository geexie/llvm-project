#include "llvm/Transforms/HabKaffeeCount/HabKaffeeCount.h"

 #define DEBUG_TYPE "HabKaffeeCount"
 #include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(funcCount, "# of functions");
ALWAYS_ENABLED_STATISTIC(arithmeticsOpersCount, "# of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(bbCount, "# of BB");

PreservedAnalyses HabKaffeePass::run(Function &F, FunctionAnalysisManager &AM) {

  funcCount += 1;

  for (auto BB = F.begin(); BB != F.end(); ++BB) {
    bbCount += 1;
    for (auto I = BB->begin(); I != BB->end(); ++I) {
      switch (I->getOpcode()) {
      case Instruction::Add:
      case Instruction::FAdd:
      case Instruction::Mul:
      case Instruction::FDiv:
      case Instruction::SDiv:
      case Instruction::UDiv:
      case Instruction::Sub:
      case Instruction::FSub:
        arithmeticsOpersCount += 1;
        break;
      }
    }
  }
  errs() << "# of functions " << funcCount << "\n";
  errs() << "# of arithmetic operations " << arithmeticsOpersCount << "\n";
  errs() << "# of BB " << bbCount << "\n";
  return PreservedAnalyses::all();
}
