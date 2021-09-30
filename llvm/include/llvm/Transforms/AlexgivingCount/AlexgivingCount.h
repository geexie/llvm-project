#ifndef LLVM_TRANSFORMS_ALEXGIVING_COUNT_H
#define LLVM_TRANSFORMS_ALEXGIVING_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

    class AlexgivingPass : public PassInfoMixin<AlexgivingPass> {
        public:
            PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        };
} // namespace llvm

#endif // LLVM_TRANSFORMS_ALEXGIVING_COUNT_H
