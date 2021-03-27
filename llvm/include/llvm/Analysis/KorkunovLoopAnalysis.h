
#ifndef LLVM_KORKUNOVLOOPANALYSIS_H_
#define LLVM_KORKUNOVLOOPANALYSIS_H_

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/IR/PassManager.h"

class KorkunovLoopAnalysis : public llvm::AnalysisInfoMixin<KorkunovLoopAnalysis> {
  friend llvm::AnalysisInfoMixin<KorkunovLoopAnalysis>;
  static llvm::AnalysisKey Key;

public:
  //size_t InvUpdatesCount = 0;
  struct Result {int InvUpdatesCount = 0;};
  Result run(llvm::Loop &L, llvm::LoopAnalysisManager &LAM, llvm::LoopStandardAnalysisResults &LSAR);
  static llvm::StringRef name();
};
//llvm::AnalysisKey KorkunovLoopAnalysis::Key;
#endif