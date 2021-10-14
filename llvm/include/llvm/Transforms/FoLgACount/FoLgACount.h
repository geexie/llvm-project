#ifndef LLVM_TRANSFORMS_FOLGA_COUNT_H
#define LLVM_TRANSFORMS_FOLGA_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class FoLgACountPass : public PassInfoMixin<FoLgACountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_FOLGA_COUNT_H 