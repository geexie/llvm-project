#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm 
{
    class ErmolaevAnalysisInfo 
    {
    public:
        void print(raw_ostream &out) const;

        int64_t powNum = 0;
        int64_t addNum = 0;
        int64_t mulNum = 0;
    };

    class ErmolaevAnalysis : public AnalysisInfoMixin<ErmolaevAnalysis> 
    {
    public:
        static AnalysisKey Key;
        using Result = ErmolaevAnalysisInfo;
        Result run(Function& F, FunctionAnalysisManager& AM);
    };
} 