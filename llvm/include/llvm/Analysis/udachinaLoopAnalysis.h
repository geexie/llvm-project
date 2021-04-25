#pragma once

#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"



using namespace llvm;

class udachinaLoopAnalysisInfo {

	public:
		int val = 0;
	
	};

class udachinaLoopAnalysis : public AnalysisInfoMixin<udachinaLoopAnalysis> {
	public:
		static StringRef name() {
			return "udachinaLoopAnalysis"; 
		};

		static AnalysisKey Key;

		using Result = udachinaLoopAnalysisInfo;

		Result run(Loop &L, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LSAR);

		
	};

