#ifndef LLVM_TRANSFORMS_AKOMYAGINASPASS_AKOMYAGINASPASS_H
#define LLVM_TRANSFORMS_AKOMYAGINASPASS_AKOMYAGINASPASS_H

#include "llvm/IR/PassManager.h"


namespace llvm {

  class AKomyaginASPass : public PassInfoMixin<AKomyaginASPass> {
  public:
    PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
  };
}
#endif
