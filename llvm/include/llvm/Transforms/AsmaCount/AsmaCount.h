ifndef LLVM_TRANSFORMS_ASMACOUNT_ASMACOUNT_H
#define LLVM_TRANSFORMS_ASMACOUNT_ASMACOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class AsmaCountPass : public PassInfoMixin<AsmaCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

}

#endif 