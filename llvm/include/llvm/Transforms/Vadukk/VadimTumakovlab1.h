#ifndef LLVM_TRANSFORMS_VADIMTUMAKOV_H
#define LLVM_TRANSFORMS_VADIMTUMAKOV_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class VADIMTUMAKOVPass : public PassInfoMixin<VADIMTUMAKOVPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM); 
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_VADIMTUMAKOV_H 