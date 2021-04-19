#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"


using namespace llvm;


class DVorobyovAnalysisInfo 
{
	public:
		void print(raw_ostream &os) const;
		int64_t muls = 0;
		int64_t powfs = 0;
		int64_t adds = 0;
};


class DVorobyovAnalysis : public AnalysisInfoMixin<DVorobyovAnalysis> {
	public:
		static AnalysisKey Key;
		using Result = DVorobyovAnalysisInfo;
		Result run(Function& F, FunctionAnalysisManager& FAM);
};