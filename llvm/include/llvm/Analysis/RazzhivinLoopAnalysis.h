#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"

namespace llvm {
    class RazzhivinLoopAnalysisInfo {
        public:
            int64_t updates = 0;
    };

    class RazzhivinLoopAnalysis : public AnalysisInfoMixin<RazzhivinLoopAnalysisInfo> {
        public:
            static AnalysisKey Key;
            using Result = RazzhivinLoopAnalysisInfo;
            Result run(Loop& loop, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA);
            static StringRef name() {return "RazzhivinLoopAnalysis";}
    };
} 