#ifndef LLVM_ANALYSIS_SELIVANOVSKAYALOOPANALYSIS_H
#define LLVM_ANALYSIS_SELIVANOVSKAYALOOPANALYSIS_H

#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"


namespace llvm {

class SelivanovskayaLoopAnalysisInfo {
public:
    int updatesCnt = 0;
};

class SelivanovskayaLoopAnalysis : public AnalysisInfoMixin<SelivanovskayaLoopAnalysis> {
public:
    static AnalysisKey Key;
    using Result = SelivanovskayaLoopAnalysisInfo;

    Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);

    static StringRef name() { return "SelivanovskayaLoopAnalysis"; }
};

} // namespace llvm

#endif