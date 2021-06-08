#pragma once

#include "llvm/Analysis/LoopInfo.h"


namespace llvm {

class PankratovaAnalysisInfo {
public:
    int totalBlocks = 0;
    int totalAdd = 0;
    int totalMul = 0;
};

class PankratovaAnalysis : public AnalysisInfoMixin<PankratovaAnalysis> {
public:
    static AnalysisKey Key;

    using Result = PankratovaAnalysisInfo;

    Result run(Function& F, FunctionAnalysisManager& AM);
};

} // namespace llvm
