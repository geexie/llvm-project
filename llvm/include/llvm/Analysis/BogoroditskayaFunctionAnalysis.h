
#ifndef LLVM_BOGORODITSKAYAFUNCTIONANALYSIS_H_
#define LLVM_BOGORODITSKAYAFUNCTIONANALYSIS_H_

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
class Function;

class BogoroditskayaFunctionAnalysisInfo {
public:

  void print(raw_ostream &OS) const;

  int64_t Num_Mull = 0;
  int64_t Num_Add = 0;
  int64_t Num_Pow = 0;
  
};

// Analysis pass
class BogoroditskayaFunctionAnalysis
    : public AnalysisInfoMixin<BogoroditskayaFunctionAnalysis> {

public:
  static AnalysisKey Key;

  using Result = BogoroditskayaFunctionAnalysisInfo;

  Result run(Function &F, FunctionAnalysisManager &FAM);
};

} // namespace llvm
#endif // LLVM_BOGORODITSKAYAFUNCTIONANALYSIS_H_
