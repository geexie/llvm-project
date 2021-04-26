#pragma once

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm {

class KMalyshevaLab3Pass : public PassInfoMixin<KMalyshevaLab3Pass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
  static bool isRequired() { return true; }
};

} // namespace llvm