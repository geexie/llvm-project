#pragma once

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm {

class pvi3 : public PassInfoMixin<pvi3> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
  static bool isRequired() { return true; }
};

} // namespace llvm