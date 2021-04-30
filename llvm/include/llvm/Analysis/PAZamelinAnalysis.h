#ifndef LLVM_ANALYSIS_PAZAMELIN_ANALYSIS_H
#define LLVM_ANALYSIS_PAZAMELIN_ANALYSIS_H

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"

namespace llvm
{
	class PAZamelinAnalysisInfo
    {
	public:
		std::size_t totalAdd = 0;
		std::size_t totalMul = 0;
		std::size_t totalPow = 0;

		void print(raw_ostream& ostream) const;
	};

	class PAZamelinAnalysis : public AnalysisInfoMixin<PAZamelinAnalysis>
    {
	public:
		static AnalysisKey Key;

		using Result = PAZamelinAnalysisInfo;

		Result run(Function& F, FunctionAnalysisManager& AM);
	};

}

#endif // LLVM_ANALYSIS_PAZAMELIN_ANALYSIS_H