#ifndef LLVM_TRANSFORMS_HABKAFFEE_COUNT_H
#define LLVM_TRANSFORMS_HABKAFFEE_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

    class HabKaffeePass : public PassInfoMixin<HabKaffeePass> {
        public:
            PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        };
} // namespace llvm

#endif // LLVM_TRANSFORMS_HABKAFFEE_COUNT_H