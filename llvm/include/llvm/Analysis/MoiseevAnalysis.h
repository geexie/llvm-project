#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm 
{
    class MoiseevAnalysisInfo 
    {
    public:
        void print(raw_ostream &out) const;

        int64_t pow_num = 0;
        int64_t add_num = 0;
        int64_t mul_num = 0;
    };

    class MoiseevAnalysis : public AnalysisInfoMixin<MoiseevAnalysis> 
    {
    public:
        static AnalysisKey Key;
        using Result = MoiseevAnalysisInfo;
        Result run(Function& F, FunctionAnalysisManager& AM);
    };
}