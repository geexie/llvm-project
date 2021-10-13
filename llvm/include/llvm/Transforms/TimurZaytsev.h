#ifndef LLVM_TRANSFORMS_TIMURZAYTSEV_H
#define LLVM_TRANSFORMS_TIMURZAYTSEV_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class TimurZaytsevPass : public PassInfoMixin<TimurZaytsevPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM); 
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_TIMURZAYTSEV_H 