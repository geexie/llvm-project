#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"


namespace llvm {

	class IlyinLoopAnalysisInfo {
	public:
		int updates = 0;
	};

	class IlyinLoopAnalysis : public AnalysisInfoMixin<IlyinLoopAnalysis> {
	public:
		static AnalysisKey Key;
		using Result = IlyinLoopAnalysisInfo;
		Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);
		static StringRef name() { return "IlyinLoopAnalysis"; }
	};

}
