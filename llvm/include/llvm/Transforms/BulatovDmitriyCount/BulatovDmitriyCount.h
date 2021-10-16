#ifndef LLVM_TRANSFORMS_BULATOVDMITRIYCOUNT_BULATOVDMITRIYCOUNT_H_
#define LLVM_TRANSFORMS_BULATOVDMITRIYCOUNT_BULATOVDMITRIYCOUNT_H_

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
  class BulatovDmitriyCountPass :
    public PassInfoMixin<BulatovDmitriyCountPass> {
   public:
      PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
  };
} // namespace llvm

#endif // LLVM_TRANSFORMS_BULATOVDMITRIYCOUNT_BULATOVDMITRIYCOUNT_H_
