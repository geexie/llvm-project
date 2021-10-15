#ifndef LLVM_TRANSFORMS_BUGROV_H
#define LLVM_TRANSFORMS_BUGROV_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class BugrovPass : public PassInfoMixin<BugrovPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM); 
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_BUGROV_H 