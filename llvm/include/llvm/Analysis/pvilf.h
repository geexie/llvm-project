#ifndef LLVM_PVIF_H_
#define LLVM_PVIF_H_

#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
class pvilf : public AnalysisInfoMixin<pvilf> {

public:
  static AnalysisKey Key;
  struct Result {
    int64_t updcounter = 0;
  };
  Result run(Loop &L, LoopAnalysisManager &LAM,
             LoopStandardAnalysisResults &LSAR);
  static StringRef name() { return "pvilf"; }
};
}

#endif