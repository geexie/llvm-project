#pragma once

#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;

class KovakimyAnalysisInfo
{
public:
  void print(raw_ostream & out);
  int64_t counterAdd = 0;
  int64_t counterMul = 0;
  int64_t counterPow = 0;
};
  
class KovakimyAnalysis : public AnalysisInfoMixin<KovakimyAnalysis>
{
public:
  static AnalysisKey Key;
  using Result = KovakimyAnalysisInfo;
  Result run(Function &F, FunctionAnalysisManager &AM);
};
