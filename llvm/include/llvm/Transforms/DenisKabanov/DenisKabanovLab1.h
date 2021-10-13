#ifndef LLVM_TRANSFORMS_DENISKABANOVLAB1_H
#define LLVM_TRANSFORMS_DENISKABANOVLAB1_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class DenisKabanovLab1Pass : public PassInfoMixin<DenisKabanovLab1Pass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM); };

} // namespace llvm

#endif // LLVM_TRANSFORMS_DENISKABANOVLAB1_H