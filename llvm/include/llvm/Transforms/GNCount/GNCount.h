#ifndef LLVM_TRANSFORMS_GNCOUNT_GNCOUNT_H
#define LLVM_TRANSFORMS_GNCOUNT_GNCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class GNCountPass : public PassInfoMixin<GNCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_GNCOUNT_GNCOUNT_H