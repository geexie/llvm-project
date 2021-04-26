#include "llvm/Analysis/KMalyshevaAnalysis.h"

namespace llvm {

AnalysisKey KMalyshevaAnalysis::Key;

KMalyshevaAnalysis::Result
KMalyshevaAnalysis::run(Function &F, FunctionAnalysisManager &FAM) {
  Result result;

  for (auto basicBlock = F.begin(); basicBlock != F.end(); ++basicBlock) {
    for (auto instruction = basicBlock->begin();
         instruction != basicBlock->end(); ++instruction) {
      if (instruction->getOpcode() == Instruction::Add ||
          instruction->getOpcode() == Instruction::FAdd) {
        result.countAdd++;
      } else if (instruction->getOpcode() == Instruction::Mul ||
                 instruction->getOpcode() == Instruction::FMul) {
        result.countMul++;
      } else if (auto callInst = dyn_cast<CallInst>(instruction)) {
        if (callInst->getCalledFunction()->getName() == "powf") {
        result.countPow++;
       }
      }
    }
  }
  return result;
}
} // namespace llvm
  /*
void KMalyshevaAnalysisInfo::print(raw_ostream &ostream) const {
  ostream << "Total pow: " << countPow << "\n"
          << "Total add: " << countAdd << "\n"
          << "Total mul: " << countMul << "\n";
}*/
 // namespace llvm