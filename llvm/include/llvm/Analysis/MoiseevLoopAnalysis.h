#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"

namespace llvm 
{
    class MoiseevLoopAnalysisInfo 
    {
    public:
        int64_t updates = 0;
    };

    class MoiseevLoopAnalysis : public AnalysisInfoMixin<MoiseevLoopAnalysis> 
    {
    public:
        static AnalysisKey Key;
        using Result = MoiseevLoopAnalysisInfo;

        Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);
        static StringRef name() { return "MoiseevLoopAnalysis"; }
    };
}