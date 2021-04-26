#ifndef LLVM_ANALYSIS_PAZAMELIN_LOOP_ANALYSIS_H
#define LLVM_ANALYSIS_PAZAMELIN_LOOP_ANALYSIS_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm
{
	class PAZamelinLoopAnalysisInfo
    {
	public:
		std::size_t updates = 0;
	};

	class PAZamelinLoopAnalysis : public AnalysisInfoMixin<PAZamelinLoopAnalysis>
    {
	public:
		static AnalysisKey Key;

		using Result = PAZamelinLoopAnalysisInfo;

		Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);
		
		static StringRef name() { return "PAZamelinLoopAnalysis"; }
	};

}

#endif // LLVM_ANALYSIS_PAZAMELIN_LOOP_ANALYSIS_H