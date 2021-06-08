#include "llvm/Transforms/Sazanov_Lab3_Pass/Sazanov_Lab3_Pass.h"
#include "llvm/Analysis/SazanovAnalysis.h"
#include "llvm/Analysis/SazanovLoopAnalysis.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/Dominators.h"

using namespace llvm;

#define DEBUG_TYPE "Sazanov_Lab3_Pass"

STATISTIC(numAdds, "Number of add");
STATISTIC(numMuls, "Number of mul");
STATISTIC(numPows, "Number of pow");
STATISTIC(numVectLoops, "Number of vectorizable loops");

void recursiveLoops(Loop* loop, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& AR)
{
	if (loop->isInnermost())
	{
		auto& result = LAM.getResult<SazanovLoopAnalysis>(*loop, AR);
		if (result.numUpd == 1)
		{
			++numVectLoops;
		}
	}
	for (Loop* subLoop : loop->getSubLoops())
	{
		recursiveLoops(subLoop, LAM, AR);
	}
}

PreservedAnalyses Sazanov_Lab3_Pass::run(Function &F, FunctionAnalysisManager &FAM)
{
	auto &result = FAM.getResult<SazanovAnalysis>(F);
	numAdds += result.numAdds;
	numMuls += result.numMuls;
	numPows += result.numPows;
	
	auto &LA = FAM.getResult<LoopAnalysis>(F);
	auto &LAM = FAM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();
	
	auto& AA = FAM.getResult<AAManager>(F);
	AssumptionCache &AC = FAM.getResult<AssumptionAnalysis>(F);
	DominatorTree &DT = FAM.getResult<DominatorTreeAnalysis>(F);
	ScalarEvolution &SE = FAM.getResult<ScalarEvolutionAnalysis>(F);
	TargetLibraryInfo &TLI = FAM.getResult<TargetLibraryAnalysis>(F);
	TargetTransformInfo &TTI = FAM.getResult<TargetIRAnalysis>(F);
	LoopStandardAnalysisResults AR = {AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr};
	
	for (auto &loop : LA)
	{
		recursiveLoops(loop, LAM, AR);
	}
	
	return PreservedAnalyses::all();
}