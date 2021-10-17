#ifndef LLVM_TRANSFORMS_SLAVOKERUCOUNT_SLAVOKERUCOUNT_H
#define LLVM_TRANSFORMS_SLAVOKERUCOUNT_SLAVOKERUCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {
    class SlavokeruCountPass : public PassInfoMixin<SlavokeruCountPass> {
    public:
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
    };
} // namespace llvm

#endif // LLVM_TRANSFORMS_SLAVOKERUCOUNT_SLAVOKERUCOUNT_H