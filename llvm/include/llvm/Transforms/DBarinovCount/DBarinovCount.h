#ifndef LLVM_TRANSFORMS_DBARINOV_COUNT_H
#define LLVM_TRANSFORMS_DBARINOV_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

	class DBarinovPass : public PassInfoMixin<DBarinovPass> {
		public:
			PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
	};

} // namespace llvm

#endif // LLVM_TRANSFORMS_DBARINOV_COUNT_H