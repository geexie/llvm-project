#ifndef LLVM_TRANSFORMS_VADUKK_H
#define LLVM_TRANSFORMS_VADUKK_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class VadukkPass : public PassInfoMixin<VadukkPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM); 
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_VADUKK_H 