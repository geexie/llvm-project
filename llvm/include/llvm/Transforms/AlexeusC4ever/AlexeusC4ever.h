#ifndef LLVM_TRANSFORMS_ALEXEUSC4EVER_ALEXEUSC4EVER_H
#define LLVM_TRANSFORMS_ALEXEUSC4EVER_ALEXEUSC4EVER_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class AlexeusC4everPass : public PassInfoMixin<AlexeusC4everPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_ALEXEUSC4EVER_ALEXEUSC4EVER_H