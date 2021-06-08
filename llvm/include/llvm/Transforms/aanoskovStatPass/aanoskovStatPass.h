#ifndef LLVM_TRANSFORMS_AANOSKOVSTATPASS_H
#define LLVM_TRANSFORMS_AANOSKOVSTATPASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/ADT/Statistic.h"

namespace llvm {

class aanoskovStatPass : public PassInfoMixin<aanoskovStatPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }
};
}

#endif