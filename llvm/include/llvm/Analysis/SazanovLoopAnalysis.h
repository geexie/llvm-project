#ifndef LLVM_ANALYSIS_SAZANOV_LOOP_ANALYSIS_H
#define LLVM_ANALYSIS_SAZANOV_LOOP_ANALYSIS_H

#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm
{
	
struct SazanovLoopAnalysisInfo
{
	int64_t numUpd = 0;
};
	
class SazanovLoopAnalysis : public AnalysisInfoMixin<SazanovLoopAnalysis>
{
public:
	static AnalysisKey Key;
	using Result = SazanovLoopAnalysisInfo;
	Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA);
	static StringRef name() { return "SazanovLoopAnalysis"; }
};

} //namespace llvm

#endif //LLVM_ANALYSIS_SAZANOV_LOOP_ANALYSIS_H