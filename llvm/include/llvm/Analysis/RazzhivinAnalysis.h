#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm {
    class RazzhivinAnalysisInfo {
        public:
            void print(raw_ostream &OS) const;

            int64_t adds = 0;
            int64_t muls = 0;
            int64_t powfs = 0;
    };

    class RazzhivinAnalysis : public AnalysisInfoMixin<RazzhivinAnalysisInfo> {
        public:
            static AnalysisKey Key;

            using Result = RazzhivinAnalysisInfo;

            Result run(Function& func, FunctionAnalysisManager& AM);
    };
}