#ifndef LLVM_TRANSFORMS_MELNIKOVLAB3PASS_MELNIKOVLAB3PASS_H
#define LLVM_TRANSFORMS_MELNIKOVLAB3PASS_MELNIKOVLAB3PASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"


namespace llvm {

class MelnikovLab3Pass : public PassInfoMixin<MelnikovLab3Pass> {
public:
  PreservedAnalyses run(Function &func, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }  
};

} 

#endif