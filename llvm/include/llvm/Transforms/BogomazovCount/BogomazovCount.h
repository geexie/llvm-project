#ifndef LLVM_TRANSFORMS_BOGOMAZOV_COUNT_H
#define LLVM_TRANSFORMS_BOGOMAZOV_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

    class BogomazovCountPass : public PassInfoMixin<BogomazovCountPass> {
        public:
            PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        };
} // namespace llvm

#endif // LLVM_TRANSFORMS_Bogomazov_COUNT_H