#include "llvm/Analysis/aanoskovCounter.h"

//#include "llvm/Analysis/FunctionPropertiesAnalysis.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

aanoskovCounterInfo
aanoskovCounterInfo::getCounts(const Function &F) {

  aanoskovCounterInfo FPI;

  //FPI.Uses = ((!F.hasLocalLinkage()) ? 1 : 0) + F.getNumUses();


  for(Function::const_iterator bb = F.begin(); bb != F.end(); ++bb)
  {
    ++FPI.BasicBlockCount;
    for(BasicBlock::const_iterator instr = bb->begin(); instr != bb->end(); ++instr)
    {
      if (auto CI = dyn_cast<CallInst>(instr))
      {
          if (auto f = CI->getCalledFunction())
          {
              if(f->getName() == "powf")
                ++FPI.PowsCount;
          }
      }
      else if (auto BO = dyn_cast<BinaryOperator>(instr))
      {
        if ( ( instr->getOpcode() == Instruction::Add ) || ( instr->getOpcode() == Instruction::FAdd ))
            ++FPI.AddsCount;
        else if ( ( instr->getOpcode() == Instruction::Mul ) || ( instr->getOpcode() == Instruction::FMul))
            ++FPI.MulsCount;
      }    
    }
  }
  return FPI;
}


void aanoskovCounterInfo::print(raw_ostream &OS) const {
  OS << "BasicBlockCount: " << BasicBlockCount << "\n"
     << "Total Adds: " << AddsCount << "\n"
     << "Total Muls: " << MulsCount << "\n"
     << "Total Pows: " << PowsCount << "\n";
}


AnalysisKey aanoskovCounter::Key;

aanoskovCounter::Result aanoskovCounter::run(Function &F, FunctionAnalysisManager &FAM) {
  return aanoskovCounterInfo::getCounts(F);
}
