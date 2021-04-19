#pragma once

#include "llvm/Analysis/LoopInfo.h"


namespace llvm {

class BaturinaAnalysisInfo {
public:
    void print(raw_ostream &ostream) const;
    int64_t totalPow = 0;
    int64_t totalAdd = 0;
    int64_t totalMul = 0;

};

class BaturinaAnalysis : public AnalysisInfoMixin<BaturinaAnalysis> {
public:
    static AnalysisKey Key;

    using Result = BaturinaAnalysisInfo;

    Result run(Function& F, FunctionAnalysisManager& FAM);
};

} 