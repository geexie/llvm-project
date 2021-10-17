#ifndef LLVM_TRANSFORMS_TITOVACOUNT_TITOVACOUNT_H
#define LLVM_TRANSFORMS_TITOVACOUNT_TITOVACOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class TitovaCountPass : public PassInfoMixin<TitovaCountPass> {
 public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

}  // namespace llvm

#endif  // LLVM_TRANSFORMS_TITOVACOUNT_TITOVACOUNT_H
