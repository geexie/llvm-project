#ifndef LLVM_ANALYSIS_MELNIKOVLAB3LOOPANALYSIS_H
#define LLVM_ANALYSIS_MELNIKOVLAB3LOOPANALYSIS_H

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopAnalysisManager.h"



namespace llvm {
class Function;


class MelnikovLab3LoopAnalysisInfo {
public:
    //static MelnikovLab3LoopAnalysisInfo getMelnikovLab3FunctionAnalysisInfo(const Function &F, const LoopInfo &LI);
    //void print(raw_ostream &OS) const;
  
    int64_t IVUpdatesCount = 0;
 
};


class MelnikovLab3LoopAnalysis : public AnalysisInfoMixin<MelnikovLab3LoopAnalysis> {
  //friend AnalysisInfoMixin<NoOpLoopAnalysis>;
  
public:
    static AnalysisKey Key;
    // int64_t IVUpdatesCount = 0;
    using Result = MelnikovLab3LoopAnalysisInfo;

    Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);

    static StringRef name() { return "MelnikovLab3LoopAnalysis";}

};

/*
class MelnikovLab3LoopAnalysisPrinter : public PassInfoMixin<MelnikovLab3LoopAnalysisPrinter> {
  raw_ostream &OS;

public:
  explicit MelnikovLab3LoopAnalysisPrinter(raw_ostream &OS) : OS(OS) {}

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
}; 
*/

} //namespace llvm
#endif