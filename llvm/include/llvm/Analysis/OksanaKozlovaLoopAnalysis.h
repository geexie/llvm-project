#pragma once
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"


using namespace llvm;

class OksanaKozlovaLoopAnalysisInfo {
public:
    int updCount = 0;
};

class OksanaKozlovaLoopAnalysis : public AnalysisInfoMixin<OksanaKozlovaLoopAnalysis> {
public:
    static AnalysisKey Key;

    using Result = OksanaKozlovaLoopAnalysisInfo;

    Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR);

    static StringRef name() { return "OksanaKozlovaLoopAnalysis"; }
};
