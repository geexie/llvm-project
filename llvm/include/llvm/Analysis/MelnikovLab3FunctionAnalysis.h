#ifndef LLVM_ANALYSIS_MELNIKOVLAB3FUNCTIONANALYSIS_H
#define LLVM_ANALYSIS_MELNIKOVLAB3FUNCTIONANALYSIS_H

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"



namespace llvm {
class Function;

class MelnikovLab3FunctionAnalysisInfo {
public:
    //static MelnikovLab3FunctionAnalysisInfo getMelnikovLab3FunctionAnalysisInfo(const Function &F, const LoopInfo &LI);
    //void print(raw_ostream &OS) const;
  
    int64_t BasicBlockCount = 0;
    int64_t FAddCount = 0;
    int64_t FMullCount = 0; 
 
};


class MelnikovLab3FunctionAnalysis : public AnalysisInfoMixin <MelnikovLab3FunctionAnalysis>  {

public:
    static AnalysisKey Key;

    using Result = MelnikovLab3FunctionAnalysisInfo; //?

    Result run (Function &F, FunctionAnalysisManager &FAM);

    static StringRef name() { return "MelnikovLab3FunctionAnalysis";}
};

/*
class MelnikovLab3FunctionAnalysisPrinter : public PassInfoMixin<MelnikovLab3FunctionAnalysisPrinter> {
  raw_ostream &OS;

public:
  explicit MelnikovLab3FunctionAnalysisPrinter(raw_ostream &OS) : OS(OS) {}

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};
*/
} // namespace llvm


#endif // LLVM_ANALYSIS_MELNIKOVLAB3FUNCTIONANALYSIS_H
