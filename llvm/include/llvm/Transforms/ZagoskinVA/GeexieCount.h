#ifndef LLVM_TRANSFORMS_ZAGOSKINVA_GEEXIECOUNT_H
#define LLVM_TRANSFORMS_ZAGOSKINVA_GEEXIECOUNT_H
#include "llvm/IR/PassManager.h"
	namespace llvm{
		class LPMUpdater;
		class GeexieCountPass : public PassInfoMixin<GeexieCountPass>{
			public:
				PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
		};
	}
#endif