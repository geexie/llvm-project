//
//  EkhorevCount.h
//
#ifndef LLVM_TRANSFORMS_EKHOREVCOUNT_EKHOREVCOUNT_H
#define LLVM_TRANSFORMS_EKHOREVCOUNT_EKHOREVCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class EkhorevCountPass : public PassInfoMixin<EkhorevCountPass> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_EKHOREVCOUNT_EKHOREVCOUNT_H
