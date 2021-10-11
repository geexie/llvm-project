#ifndef LLVM_TRANSFORMS_SHAIDI_PASS_H
#define LLVM_TRANSFORMS_SHAIDI_PASS_H

#include "llvm/IR/PassManager.h"

namespace llvm {

    class shaidiPass : public PassInfoMixin<shaidiPass> {
        public:
            PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        };
} // namespace llvm

#endif // LLVM_TRANSFORMS_SHAIDI_PASS_H