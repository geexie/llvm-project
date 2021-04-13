#pragma once

#include "llvm/Analysis/KovakimyAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"


using namespace llvm;

AnalysisKey KovakimyAnalysis::Key;

void KovakimyAnalysisInfo::print(raw_ostream &os)
{
	
  os << "Adds: "  << counterAdd << "/n";
  os << "Muls: "  << counterMul << "/n";
  os << "Powfs: " << counterPow << "/n";
	
  return;
}

KovakimyAnalysis::Result KovakimyAnalysis::run(Function& F, FunctionAnalysisManager& AM)
{
  Result result;
  for (Function::iterator iterF = F.begin(); iterF != F.end(); ++iterF)
  {
    for (BasicBlock::iterator iterB = iterF->begin(); iterB != iterF->end(); ++iterB)
    {
	  if (std::string(iterB->getOpcodeName()) == "add" || std::string(iterB->getOpcodeName()) == "fadd")
	    result.counterAdd++;
	  if (std::string(iterB->getOpcodeName()) == "mul" || std::string(iterB->getOpcodeName()) == "fmul")
	    result.counterMul++;

    }
  }

  for (Instruction &I : instructions(F))
    if (CallInst *C = dyn_cast<CallInst>(&I)) 
	  if (C->getCalledFunction()->getName() == "powf")
	    result.counterPow++;

  return result;
}
