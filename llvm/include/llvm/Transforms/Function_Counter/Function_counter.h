#ifndef LLVM_TRANSFORMS_FUNCTION_COUNTER_H
#define LLVM_TRANSFORMS_FUNCTION_COUNTER_H

#include "llvm/IR/PassManager.h"

namespace llvm {

    class Function_counter_pass : public PassInfoMixin<Function_counter_pass> {
        public:
            PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        };
} // namespace llvm

#endif // LLVM_TRANSFORMS_FUNCTION_COUNTER_H