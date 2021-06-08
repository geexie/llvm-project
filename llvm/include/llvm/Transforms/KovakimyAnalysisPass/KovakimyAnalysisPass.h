#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

using namespace llvm;

class KovakimyAnalysisPass : public PassInfoMixin<KovakimyAnalysisPass>
{
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
  static bool isRequired()
  { 
    return true; 
  } 
};
