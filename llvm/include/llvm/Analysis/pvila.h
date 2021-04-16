#pragma once

#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm {

class pvilainf {
public:
  int updatecounter = 0;
};

class pvila : public AnalysisInfoMixin<pvila> {
public:
  static AnalysisKey Key;

  using Result = pvilainf;

  Result run(Loop &L, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LSAR);

  static StringRef name() { return "pvila"; }
};
}