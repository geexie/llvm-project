#pragma once

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"


namespace llvm {

class PankratovaLoopAnalysisInfo {
public:
    int count = 0;
};


class PankratovaLoopAnalysis : public AnalysisInfoMixin<PankratovaLoopAnalysis> {
public:
    static AnalysisKey Key;

    using Result = PankratovaLoopAnalysisInfo;

    Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);
};

} // namespace llvm