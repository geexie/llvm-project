
#ifndef LLVM_KORKUNOVANALYSISPASS_H_
#define LLVM_KORKUNOVANALYSISPASS_H_

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
class Function;

class KorkunovAnalysisPassInfo {
public:
  static KorkunovAnalysisPassInfo getKorkunovAnalysisPassInfo(const Function &F,
                                                          const LoopInfo &LI);

  void print(raw_ostream &OS) const;

  int64_t tfmul = 0;
  int64_t tpowf = 0;
  int64_t tfadd = 0;

};

// Analysis pass
class KorkunovAnalysisPass
    : public AnalysisInfoMixin<KorkunovAnalysisPass> {

public:
  static AnalysisKey Key;

  using Result = KorkunovAnalysisPassInfo;

  Result run(Function &F, FunctionAnalysisManager &FAM);
};

/// Printer pass for the FunctionPropertiesAnalysis results.
class KorkunovAnalysisPassPrinter
    : public PassInfoMixin<KorkunovAnalysisPassPrinter> {
  raw_ostream &OS;

public:
  explicit KorkunovAnalysisPassPrinter(raw_ostream &OS) : OS(OS) {}

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm
#endif
