#ifndef LLVM_TRANSFORMS_NIKITACOUNT_NIKITACOUNT_H
#define LLVM_TRANSFORMS_NIKITACOUNT_NIKITACOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {
    class NikitaCountPass : public PassInfoMixin<NikitaCountPass> {
    public:
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
    };
} // namespace llvm

#endif // LLVM_TRANSFORMS_NIKITACOUNT_NIKITACOUNT_H