#pragma once

#include "llvm/Analysis/DVorobyovAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"


using namespace llvm;


AnalysisKey DVorobyovAnalysis::Key;
void DVorobyovAnalysisInfo::print(raw_ostream &os) const 
{
	os << "Adds: " << adds << "\n";
	os << "Muls: " << muls << "\n";
	os << "Powfs: " << powfs << "\n";
	return;
}


DVorobyovAnalysis::Result DVorobyovAnalysis::run(Function& F, FunctionAnalysisManager& FAM)
{
	Result result;
	for (auto IBB = F.begin(); IBB != F.end(); ++IBB)
	{
		for (auto IF = IBB->begin(); IF != IBB->end(); ++IF)
		{
			if (IF->getOpcode() == Instruction::Add || IF->getOpcode() == Instruction::FAdd)
				result.adds++;
			if (IF->getOpcode() == Instruction::Mul || IF->getOpcode() == Instruction::FMul)
				result.muls++;
		}
	}

	for (auto& IF :IFuctions(F))
	{
		if (auto callInst = dyn_cast<CallInst>(&IF))
			if (callInst->getCalledFunction()->getName() == "powf")
				result.powfs++;
	}
	return result;
}