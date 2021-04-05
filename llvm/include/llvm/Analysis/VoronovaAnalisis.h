#pragma once
#define DEBUG_TYPE "VoronovaAnalisis"

#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/PassManager.h"


#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/ADT/SmallPtrSet.h"

#include "llvm/IR/CFG.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"

#include "llvm/Pass.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Analysis/LoopInfo.h"
#include <algorithm>
#include <utility>


namespace llvm {



	class VoronovaAnalisisInfo 
	{
		public:
		
			int64_t CountPows = 0;
			int64_t CountAdds = 0;
			int64_t CountMulls = 0;
			void output(raw_ostream& OS);
	};

	class VoronovaAnalisis : public AnalysisInfoMixin<VoronovaAnalisis>
	{
		public:
			static AnalysisKey Key;
			using Result = VoronovaAnalisisInfo;
			Result run(Function& F, FunctionAnalysisManager& FAM);
	};

}