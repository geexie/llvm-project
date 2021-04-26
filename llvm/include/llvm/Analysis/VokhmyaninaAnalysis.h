#pragma once

#include "llvm/Analysis/LoopInfo.h"


namespace llvm {

class VokhmyaninaAnalysisInfo {
public:
    void print(raw_ostream &out) const;
    int64_t total_pow = 0;
    int64_t total_add = 0;
    int64_t total_mul = 0;

};

class VokhmyaninaAnalysis : public AnalysisInfoMixin<VokhmyaninaAnalysis> {
public:
    static AnalysisKey Key;

    using Result = VokhmyaninaAnalysisInfo;

    Result run(Function& F, FunctionAnalysisManager& AM);
};

}