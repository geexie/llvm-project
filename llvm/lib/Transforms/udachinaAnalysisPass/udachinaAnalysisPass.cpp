#include "llvm/Transforms/udachinaAnalysisPass/udachinaAnalysisPass.h"
#include "llvm/Analysis/udachinaAnalysis.h"
#include "llvm/Analysis/udachinaLoopAnalysis.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

#define DEBUG_TYPE "udachinaAnalysispass"
using namespace llvm;

STATISTIC(TotalLoops, "Value of loops");
STATISTIC(value_of_add, "Value of arithmetic instructions");
STATISTIC(value_of_mul, "Value of muls");
STATISTIC(value_of_block, "Value of basic blocks");

void valLoops(Loop *L, LoopAnalysisManager &LAM,
              LoopStandardAnalysisResults &LSAR) {
  if (L->isInnermost()) {
    auto &result = LAM.getResult<udachinaLoopAnalysis>(*L, LSAR);
    if (result.val == 1)
      TotalLoops++;
  } else {
    for (Loop *loop : L->getSubLoops())
      valLoops(loop, LAM, LSAR);
  }
};
PreservedAnalyses udachinaAnalysisPass::run(Function &F, FunctionAnalysisManager &AM)
{
	auto &result = AM.getResult<udachinaAnalysis>(F);

	value_of_mul += result.val_mul;
	value_of_add += result.val_add;
	value_of_block += result.val_block;

	result.print(errs());

	auto& LA = AM.getResult<LoopAnalysis>(F);
	auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();
	auto& AA = AM.getResult<AAManager>(F);

	AssumptionCache &AC = AM.getResult<AssumptionAnalysis>(F);
	DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
	ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
	TargetLibraryInfo &TLI = AM.getResult<TargetLibraryAnalysis>(F);
	TargetTransformInfo &TTI = AM.getResult<TargetIRAnalysis>(F);


	LoopStandardAnalysisResults LSAR = { AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr };

	for (auto& loop : LA)
		valLoops(loop, LAM, LSAR);

	return PreservedAnalyses::all();
}



