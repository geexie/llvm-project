#ifndef LLVM_TRANSFORMS_ANYASCHEN_COUNT_H
#define LLVM_TRANSFORMS_ANYASCHEN_COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class AnyaSchenCountPass : public PassInfoMixin<AnyaSchenCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_ANYASCHEN_H