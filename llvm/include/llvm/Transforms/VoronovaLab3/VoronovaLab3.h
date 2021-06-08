#pragma once
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Utils/LoopUtils.h"



namespace llvm {

	class VoronovaLab3 : public PassInfoMixin<VoronovaLab3> 
	{
		public:
			PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
			static bool isRequired() { return true; }
	};

}
