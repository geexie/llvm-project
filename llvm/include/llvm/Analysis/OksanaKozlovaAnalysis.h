#pragma once
#include "llvm/Analysis/LoopInfo.h"


using namespace llvm;

class OksanaKozlovaAnalysisInfo {
public:
    void print(raw_ostream &ostream) const;
    size_t totalFuncs = 0;
    size_t totalArithmInstrs = 0;
    size_t totalBasicBlocks = 0;

};

class OksanaKozlovaAnalysis : public AnalysisInfoMixin<OksanaKozlovaAnalysis> {
public:
    static AnalysisKey Key;

    using Result = OksanaKozlovaAnalysisInfo;

    Result run(Function& F, FunctionAnalysisManager& AM);
};
