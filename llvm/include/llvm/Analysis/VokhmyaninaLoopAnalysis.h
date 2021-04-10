#pragma once

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"


namespace llvm {

class VokhmyaninaLoopAnalysisInfo {
public:
    int updates_count = 0;
};

class VokhmyaninaLoopAnalysis : public AnalysisInfoMixin<VokhmyaninaLoopAnalysis> {
public:
    static AnalysisKey Key;

    using Result = VokhmyaninaLoopAnalysisInfo;

    Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);

    static StringRef name() { return "VokhmyaninaLoopAnalysis"; }
};
}
