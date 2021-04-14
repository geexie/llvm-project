#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"

namespace llvm {
    class VolokhLoopAnalysisInfo {
        public:
            int64_t updates = 0;
    };

    class VolokhLoopAnalysis : public AnalysisInfoMixin<VolokhLoopAnalysisInfo> {
        public:
            static AnalysisKey Key;
            using Result = VolokhLoopAnalysisInfo;
            Result run(Loop& loop, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA);
            static StringRef name() {return "VolokhLoopAnalysis";}
    };
}