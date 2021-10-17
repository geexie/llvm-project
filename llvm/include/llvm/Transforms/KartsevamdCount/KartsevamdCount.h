#ifndef LLVM_TRANSFORMS_KARTSEVAMDCOUNT_KARTSEVAMDCOUNT_H
#define LLVM_TRANSFORMS_KARTSEVAMDCOUNT_KARTSEVAMDCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class KartsevamdCountPass : public PassInfoMixin<KartsevamdCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_KARTSEVAMDCOUNT_KARTSEVAMDCOUNT_H