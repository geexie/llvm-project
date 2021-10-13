#ifndef LLVM_TRANSFORMS_AKLCOUNT_AKLCOUNT_H
#define LLVM_TRANSFORMS_AKLCOUNT_AKLCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class AklCountPass : public PassInfoMixin<AklCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_AKLCOUNT_AKLCOUNT_H