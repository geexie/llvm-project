#ifndef LLVM_TRANSFORMS_MY_COUNT_H
#define LLVM_TRANSFORMS_MY_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

	class MyCountPass : public PassInfoMixin<MyCountPass> {
	public:
		PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
	};
} // namespace llvm

#endif // LLVM_TRANSFORMS_MY_COUNT_Hs