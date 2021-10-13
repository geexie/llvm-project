#ifndef LLVM_TRANSFORMS_IVANOVD4COUNT_IVANOVD4COUNT_H
#define LLVM_TRANSFORMS_IVANOVD4COUNT_IVANOVD4COUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class Ivanovd4CountPass : public PassInfoMixin<Ivanovd4CountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif 