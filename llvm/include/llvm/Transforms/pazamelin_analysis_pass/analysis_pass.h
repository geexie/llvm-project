#ifndef LLVM_TRANSFORMS_PAZAMELIN_ANALYSIS_PASS_H
#define LLVM_TRANSFORMS_PAZAMELIN_ANALYSIS_PASS_H

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm
{

	class PAZamelinAnalysisPass : public PassInfoMixin<PAZamelinAnalysisPass>
	{
	public:
  		PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);

  		static bool isRequired() { return true; }

  	// void handleLoop(const Loop* L) const;
	};

} // namespace llvm

#endif // LLVM_TRANSFORMS_PAZAMELIN_PASS_H 