#ifndef LLVM_TRANSFORMS_KISOZINOVCOUNT_KISOZINOVCOUNT_H
#define LLVM_TRANSFORMS_KISOZINOVCOUNT_KISOZINOVCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class KisozinovCountPass : public PassInfoMixin<KisozinovCountPass> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_KISOZINOVCOUNT_KISOZINOVCOUNT_H