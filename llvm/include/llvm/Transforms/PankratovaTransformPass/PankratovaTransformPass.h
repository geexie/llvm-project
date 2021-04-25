#pragma once

#include "llvm/Analysis/PankratovaAnalysis.h"
#include "llvm/Analysis/PankratovaLoopAnalysis.h"

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

namespace llvm {

class PankratovaTransformPass : public PassInfoMixin<PankratovaTransformPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }

};

} // namespace llvm