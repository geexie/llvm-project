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


#define DEBUG_TYPE "transform pass by Pankratova"

STATISTIC(TotalVectorizableLoops, "Number of Vectorizable Loops");
STATISTIC(TotalBlocks, "Number of Basic blocks");
STATISTIC(TotalAdd, "Number of Add instructions");
STATISTIC(TotalMul, "Number of Mul instructions");


namespace llvm {

class PankratovaTransformPass : public PassInfoMixin<PankratovaTransformPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }

};

} // namespace llvm