#pragma once

#include "llvm/Analysis/LoopInfo.h"


namespace llvm {

    class AvmusatovAnalysisInfo {
    public:
        size_t powOperationCount = 0;
        size_t addOperationCount = 0;
        size_t mulOperationCount = 0;
        size_t basicBlockCount = 0;
        
        void printResults(raw_ostream& ostream) const;
    };

    class AvmusatovAnalysis : public AnalysisInfoMixin<AvmusatovAnalysis> {
    public:
        static AnalysisKey Key;

        using Result = AvmusatovAnalysisInfo;

        Result run(Function& F, FunctionAnalysisManager& FAM);
    };

}