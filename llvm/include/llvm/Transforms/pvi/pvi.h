#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Instruction.h"

namespace llvm {

class pvi : public PassInfoMixin<pvi> {
	public:
	  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
	  static bool isRequired() { return true; }
};

} 