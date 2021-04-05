#ifndef LLVM_PVIF_H_
#define LLVM_PVIF_H_

#include "llvm/Analysis/FunctionPropertiesAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
class Function;

class pvifi {
public:
  static pvifi getpvifi(const Function &F, const LoopInfo &LI);

  void print(raw_ostream &OS) const;

  int64_t addcounter = 0;
  int64_t mulcounter = 0;
  int64_t bbcounter = 0;
};

class pvif : public AnalysisInfoMixin<pvif> {

public:
  static AnalysisKey Key;

  using Result = pvifi;

  Result run(Function &F, FunctionAnalysisManager &FAM);
};

class pvifpp : public PassInfoMixin<pvifpp> {
  raw_ostream &OS;

public:
  explicit pvifpp(raw_ostream &OS) : OS(OS) {}

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
};

} 
#endif 