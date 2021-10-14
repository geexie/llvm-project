#ifndef LLVM_TRANSFORMS_ROGOZYANCOUNT_ROGOZYANCOUNT_H
#define LLVM_TRANSFORMS_ROGOZYANCOUNT_ROGOZYANCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class RogozyanCountPass : public PassInfoMixin<RogozyanCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_ROGOZYANCOUNT_ROGOZYANCOUNT_H 
