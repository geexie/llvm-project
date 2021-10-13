#ifndef LLVM_TRANSFORMS_EUGINEERD_COUNT_H
#define LLVM_TRANSFORMS_EUGINEERD_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class EugineerdCountPass : public PassInfoMixin<EugineerdCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif
