#ifndef LLVM_TRANSFORMS_LAB1_H
#define LLVM_TRANSFORMS_LAB1_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class Lab1Pass : public PassInfoMixin<Lab1Pass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_HELLONEW_HELLOWORLD_H
