#ifndef LLVM_TRANSFORMS_GOLOVANOV_CTR_H
#define LLVM_TRANSFORMS_GOLOVANOV_CTR_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm {

    class Golovanov_CTR_pass : public PassInfoMixin<Golovanov_CTR_pass> {
        public:
            PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        };
} // namespace llvm

#endif // LLVM_TRANSFORMS_GOLOVANOV_CTR_H
