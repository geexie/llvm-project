#pragma once

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"

namespace llvm {

    class AvmusatovLoopAnalysisInfo {
    public:
        int updatesCount = 0;
    };

    class AvmusatovLoopAnalysis : public AnalysisInfoMixin<AvmusatovLoopAnalysis> {
    public:
        static AnalysisKey Key;

        using Result = AvmusatovLoopAnalysisInfo;

        Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);

        static StringRef name() { return "AvmusatovLoopAnalysis"; }
    };
}