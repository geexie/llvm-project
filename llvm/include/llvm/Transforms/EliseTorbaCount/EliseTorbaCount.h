#ifndef LLVM_TRANSFORMS_ELISETORBACOUNT_ELISETORBACOUNT_H
#define LLVM_TRANSFORMS_ELISETORBACOUNT_ELISETORBACOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class EliseTorbaCountPass : public PassInfoMixin<EliseTorbaCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_ELISETORBACOUNT_ELISETORBACOUNT_H