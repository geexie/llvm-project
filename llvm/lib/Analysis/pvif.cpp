#include "llvm/Analysis/pvif.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

pvifi
pvifi::getpvifi(const Function &F, const LoopInfo &LI) {

  pvifi inf;

  for (const BasicBlock &BB : F) {
    inf.bbcounter++;
    for (const Instruction &I : BB) {
      std::string inst = std::string(I.getOpcodeName());
      if (inst == "add" || inst == "fadd")
        inf.addcounter++;
      if (inst == "mul" || inst == "fmul")
        inf.mulcounter++;
    }
  }
  return inf;
}

void pvifi::print(raw_ostream &OS) const {
  OS << "+: " << addcounter << "\n"
     << "*: " << mulcounter << "\n"
     << "bb: " << bbcounter << "\n";
}

AnalysisKey pvif::Key;

pvifi 
pvif::run(Function &F, FunctionAnalysisManager &FAM) {
  return pvifi::getpvifi(
      F, FAM.getResult<LoopAnalysis>(F));
}

PreservedAnalyses 
pvipp::run(Function &F, FunctionAnalysisManager &FAM) {
  FAM.getResult<pvilf>(F).print(OS);
  return PreservedAnalyses::all();
}