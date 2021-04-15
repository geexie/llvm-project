#include "llvm/Analysis/pvia.h"

namespace llvm {

AnalysisKey pvia::Key;

pvia::Result pvia::run(Function &F, FunctionAnalysisManager &FAM) {
  Result result;

  for (auto basicBlock = F.begin(); basicBlock != F.end(); ++basicBlock) {
    for (auto instruction = basicBlock->begin();
         instruction != basicBlock->end(); ++instruction) {
      if (instruction->getOpcode() == Instruction::Add ||
          instruction->getOpcode() == Instruction::FAdd) {
        result.Addcounter++;
      } else if (instruction->getOpcode() == Instruction::Mul ||
                 instruction->getOpcode() == Instruction::FMul) {
        result.Mulcounter++;
      } else if (auto callInst = dyn_cast<CallInst>(instruction)) {
        if (callInst->getCalledFunction()->getName() == "powf") {
          result.Powcounter++;
        }
      }
    }
  }
  return result;
}

void pviaInfo::print(raw_ostream &ostream) const {
  ostream << "pow counter: " << Powcounter << "\n"
          << "add counter: " << Addcounter << "\n"
          << "mul counter: " << Mulcounter << "\n";
}
} // namespace llvm