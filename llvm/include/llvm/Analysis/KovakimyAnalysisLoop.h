#pragma once

#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;
class KovakimyAnalysisLoopInfo
{
public:
  unsigned int updates = 0;
};

class KovakimyAnalysisLoop : public AnalysisInfoMixin<KovakimyAnalysisLoop>
{
public:
  static AnalysisKey Key;
  using Result = KovakimyAnalysisLoopInfo;
  Result run(Loop &L, LoopAnalysisManager &LAM, LoopStandardAnalysisResults & LSAR);
  static StringRef name()
  {
    return "KovakimyAnalysisLoop";
  }
};
