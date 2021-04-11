#pragma once
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/IR/PassManager.h"


using namespace llvm;

class udachinaAnalysisPass : public PassInfoMixin<udachinaAnalysisPass> {

public:
	static bool isRequired() {
		return true;
	};
	PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
	
	
};
