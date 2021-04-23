#ifndef LLVM_ANALYSIS_SAZANOV_ANALYSIS_H
#define LLVM_ANALYSIS_SAZANOV_ANALYSIS_H

#include "llvm/Analysis/LoopInfo.h"

namespace llvm
{
	
struct SazanovAnalysisInfo
{
	int64_t numAdds = 0;
	int64_t numMuls = 0;
	int64_t numPows = 0;
};

class SazanovAnalysis : public AnalysisInfoMixin<SazanovAnalysis>
{
public:
	static AnalysisKey Key;
	using Result = SazanovAnalysisInfo;
	Result run(Function &F, FunctionAnalysisManager &FAM);
};

} //namespace llvm

#endif //LLVM_ANALYSIS_SAZANOV_ANALYSIS_H