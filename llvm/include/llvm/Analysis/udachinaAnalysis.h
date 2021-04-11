#pragma once

#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"


using namespace llvm;

class udachinaAnalysisInfo {

public:
	void print(raw_ostream &ostream) const;
	
	int val_mul = 0;
	int val_block = 0;
	int val_add = 0;

};

class udachinaAnalysis : public AnalysisInfoMixin<udachinaAnalysis> {
public:
	static AnalysisKey Key;

	using Result = udachinaAnalysisInfo;

	Result run(Function &F, FunctionAnalysisManager &AM);
};



