#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"

STATISTIC(funcDefCount, "Number of function definitions");
STATISTIC(loopsCount, "Number of loops");
STATISTIC(basicBlocksCount, "Number of basic blocks");
STATISTIC(mulOperationCount, "Number of mul operations");
STATISTIC(addOperationCount, "Number of add operations");

namespace llvm {

  class TsyplakovCounter : public PassInfoMixin<TsyplakovCounter> {
  public:
    PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
    static bool isRequired() { return true; }
  };
} // namespace llvm

#endif //LLVM_TRANSFORMS_TSYPLAKOVCOUNTER_TSYPLAKOVCOUNTER_H
