#ifndef LLVM_TRANSFORMS_KUZNETSOVMIKHAILCOUNT_KUZNETSOVMIKHAILCOUNT_H_
#define LLVM_TRANSFORMS_KUZNETSOVMIKHAILCOUNT_KUZNETSOVMIKHAILCOUNT_H_

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm {
  class KuznetsovMikhailCountPass :
    public PassInfoMixin<KuznetsovMikhailCountPass> {
   public:
      PreservedAnalyses run(Function &F,
                            FunctionAnalysisManager &AM);
  };
} // namespace llvm

#endif // LLVM_TRANSFORMS_KUZNETSOVMIKHAILCOUNT_KUZNETSOVMIKHAILCOUNT_H_
