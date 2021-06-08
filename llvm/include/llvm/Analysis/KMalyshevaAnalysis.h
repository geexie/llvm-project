#pragma once

#include "llvm/Analysis/LoopInfo.h"

namespace llvm {

class KMalyshevaAnalysisInfo {
public:
  
  int64_t countPow = 0;
  int64_t countAdd = 0;
  int64_t countMul = 0;
};

class KMalyshevaAnalysis : public AnalysisInfoMixin<KMalyshevaAnalysis> {
public:
  static AnalysisKey Key;

  using Result = KMalyshevaAnalysisInfo;

  Result run(Function &F, FunctionAnalysisManager &FAM);
};

} // namespace llvm