#pragma once

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"


namespace llvm {

	class IlyinAnalysisInfo {
	public:
		size_t pows = 0;
		size_t adds = 0;
		size_t muls = 0;
		size_t basicBlocks = 0;
		void print(raw_ostream& ostream) const;
	};

	class IlyinAnalysis : public AnalysisInfoMixin<IlyinAnalysis> {
	public:
		static AnalysisKey Key;
		using Result = IlyinAnalysisInfo;
		Result run(Function& F, FunctionAnalysisManager& FAM);
	};

}
