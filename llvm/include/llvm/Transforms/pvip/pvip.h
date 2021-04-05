#ifndef LLVM_PVIF_H_
#define LLVM_PVIF_H_

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/PassManager.h"

#include "llvm/Analysis/FunctionPropertiesAnalysis.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/pvilf.h"
#include "llvm/Analysis/pvif.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Dominators.h"

namespace llvm {

class pvip : public PassInfoMixin<pvip> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
  static bool isRequired() { return true; }
};

}

#endif