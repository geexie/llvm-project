#ifndef LLVM_AANOSKOVCOUNTER_H_
#define LLVM_AANOSKOVCOUNTER_H_

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
class Function;

class aanoskovCounterInfo {
public:
  static aanoskovCounterInfo getCounts(const Function &F);

  int64_t BasicBlockCount = 0;
  int64_t AddsCount = 0;
  int64_t MulsCount = 0;
  int64_t PowsCount = 0;
  void print(raw_ostream &OS) const;
};

// Analysis pass
class aanoskovCounter
    : public AnalysisInfoMixin<aanoskovCounter> {

public:
  static AnalysisKey Key;

  using Result = aanoskovCounterInfo;

  Result run(Function &F, FunctionAnalysisManager &FAM);
};

} // namespace llvm
#endif 
