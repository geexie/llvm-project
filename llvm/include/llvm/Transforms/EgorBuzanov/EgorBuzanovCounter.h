#ifndef LLVM_TRANSFORMS_EGORBUZANOV_COUNTER_H
#define LLVM_TRANSFORMS_EGORBUZANOV_COUNTER_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class EgorBuzanovCounter : public PassInfoMixin<EgorBuzanovCounter> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};
} // namespace llvm

#endif // LLVM_TRANSFORMS_EGORBUZANOV_COUNTER_H
