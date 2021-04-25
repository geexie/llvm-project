#pragma once

#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm {

class KMalyshevaLoopAnalysisInfo {
public:

  int upd_count = 0;

};

class KMalyshevaLoopAnalysis : public AnalysisInfoMixin<KMalyshevaLoopAnalysis> {
public:
  static AnalysisKey Key;

  using Result = KMalyshevaLoopAnalysisInfo;

  Result run(Loop &L, LoopAnalysisManager &LAM,
             LoopStandardAnalysisResults &LSAR);

  static StringRef name() { return "KMalyshevaLoopAnalysis"; }
};
} // namespace llvm