#include "llvm/Transforms/pazamelin_analysis_pass/analysis_pass.h"
#include "llvm/Analysis/PAZamelinAnalysis.h"
#include "llvm/Analysis/PAZamelinLoopAnalysis.h"


#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"

#define DEBUG_TYPE "pazamelin_analysis_pass"

namespace llvm
{
    STATISTIC(TotalVectorizableLoops, "Number of vectorizable loops");
    STATISTIC(TotalAdd, "Number of add instructions");
    STATISTIC(TotalMul, "Number of add instructions");
    STATISTIC(TotalPow, "Number of pow and powf instructions");

	void handleLoop(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR)
    {
		if (L->isInnermost())
        {
			auto& result = LAM.getResult<PAZamelinLoopAnalysis>(*L, LSAR);
			if (result.updates == 1)
            {
				TotalVectorizableLoops++;
			}
		}

		for (Loop* loop : L->getSubLoops())
        {
			handleLoop(loop, LAM, LSAR);
		}

	}

	PreservedAnalyses PAZamelinAnalysisPass::run(Function& F, FunctionAnalysisManager& AM) {

		auto& result = AM.getResult<PAZamelinAnalysis>(F);
		result.print(errs());

		TotalAdd += result.totalAdd;
		TotalMul += result.totalMul;
		TotalPow += result.totalPow;

		auto& LA = AM.getResult<LoopAnalysis>(F);
		auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();
		auto& AA = AM.getResult<AAManager>(F);
		auto& AC = AM.getResult<AssumptionAnalysis>(F);
		auto& DT = AM.getResult<DominatorTreeAnalysis>(F);
		auto& SE = AM.getResult<ScalarEvolutionAnalysis>(F);
		auto& TLI = AM.getResult<TargetLibraryAnalysis>(F);
		auto& TTI = AM.getResult<TargetIRAnalysis>(F);

		LoopStandardAnalysisResults AR = { AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr };

		for (auto& L : LA)
        {
			handleLoop(L, LAM, AR);
		}

		return PreservedAnalyses::all();
	}

};
