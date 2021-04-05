#pragma once

#include "llvm/IR/PassManager.h"


using namespace llvm;


class DVorobyovAnalysisPass : public PassInfoMixin<DVorobyovAnalysisPass> 
{
	PreservedAnalyses run(Function& F, FunctionAnalysisManager& FAM);
	static bool isRequired()
		return true;
};