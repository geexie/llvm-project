#pragma once
#ifndef LLVM_TRANSFORMS_KMLAB1PASS_KMLAB1PASS_H
#define LLVM_TRANSFORMS_KMLAB1PASS_KMLAB1PASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"


namespace llvm {

	class KMLab1Pass : public PassInfoMixin<KMLab1Pass> {
	public:
		PreservedAnalyses run(Function& func, FunctionAnalysisManager& AM);

		static bool isRequired() { return true; }  // works even whan all optimisations are turned off 
	};

} // namespace llvm

#endif 