#ifndef LLVM_TRANSFORMS_NIKDEMOSHOW_COUNT_H
#define LLVM_TRANSFORMS_NIKDEMOSHOW_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

  class NikDemoShowPass : public PassInfoMixin<NikDemoShowPass> {
    public:
      PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
  };
} // namespace llvm

#endif // LLVM_TRANSFORMS_NIKDEMOSHOW_COUNT_Hs
