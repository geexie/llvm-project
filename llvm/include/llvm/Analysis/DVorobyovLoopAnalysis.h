#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"


using namespace llvm;


class DVorobyovLoopAnalysisInfo
{
	public:
		int64_t updates_counter = 0;
};


class DVorobyovLoopAnalysis : public AnalysisInfoMixin<DVorobyovLoopAnalysisInfo> 
{
	public:
		static AnalysisKey Key;
		using Result = DVorobyovLoopAnalysisInfo;
		Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA);
		static StringRef name()
			return "DVorobyovLoopAnalysis";
};