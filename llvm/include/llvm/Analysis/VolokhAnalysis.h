#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm {
    class VolokhAnalysisInfo {
        public:
            void print(raw_ostream &OS) const;

            int64_t adds = 0;
            int64_t muls = 0;
            int64_t powfs = 0;
    };

    class VolokhAnalysis : public AnalysisInfoMixin<VolokhAnalysis> {
        public:
            static AnalysisKey Key;

            using Result = VolokhAnalysisInfo;

            Result run(Function& func, FunctionAnalysisManager& AM);
    };
}