#pragma once

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"


namespace llvm {

class BaturinaLoopAnalysisInfo {
public:
    int updCnt = 0;
};

class BaturinaLoopAnalysis : public AnalysisInfoMixin<BaturinaLoopAnalysis> {
public:
    static AnalysisKey Key;

    using Result = BaturinaLoopAnalysisInfo;

    Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);

    static StringRef name() { return "BaturinaLoopAnalysis"; }
};
}