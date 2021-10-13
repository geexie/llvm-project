#ifndef LLVM_TRANSFORMS_MALININDD_COUNT_H
#define LLVM_TRANSFORMS_MALININDD_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

    class MalininDDPass : public PassInfoMixin<MalininDDPass> {
        public:
            PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        };
} // namespace llvm

#endif // LLVM_TRANSFORMS_MALININDD_COUNT_H