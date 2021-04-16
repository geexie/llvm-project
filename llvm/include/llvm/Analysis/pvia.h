#pragma once

#include "llvm/Analysis/LoopInfo.h"

namespace llvm {

class pviainf {
public:
  void print(raw_ostream &ostream) const;
  int64_t Powcounter = 0;
  int64_t Addcounter = 0;
  int64_t Mulcounter = 0;
};

class pvia : public AnalysisInfoMixin<pvia> {
public:
  static AnalysisKey Key;

  using Result = pviainf;

  Result run(Function &F, FunctionAnalysisManager &FAM);
};

} // namespace llvm