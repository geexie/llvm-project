#include "llvm/Transforms/IlyinAnalysisPass/IlyinAnalysisPass.h"
#include "llvm/Analysis/IlyinAnalysis.h"
#include "llvm/Analysis/IlyinLoopAnalysis.h"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

#define DEBUG_TYPE "IlyinAnalysisPass"

namespace llvm {

	STATISTIC(NumbOfPows, "Number of basic blocks");
	STATISTIC(NumbOfBasicBlocks, "Number of basic blocks");
	STATISTIC(NumbOfVectorizableLoops, "Number of loops");
	STATISTIC(NumbOfAdds, "Number of add instructions");
	STATISTIC(NumbOfMulls, "Number of mul instructions");

	static void handleLoop(Loop* L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
		if (L->isInnermost()) {
			auto& result = LAM.getResult<IlyinLoopAnalysis>(*L, LSAR);
			if (result.updates == 1) {
				NumbOfVectorizableLoops++;
			}
		}

		for (Loop* loop : L->getSubLoops()) {
			handleLoop(loop, LAM, LSAR);
		}

	}

	PreservedAnalyses IlyinAnalysisPass::run(Function& F, FunctionAnalysisManager& AM) {

		auto& result = AM.getResult<IlyinAnalysis>(F);

		NumbOfAdds += result.adds;
		NumbOfMulls += result.muls;
		NumbOfPows += result.pows;
		NumbOfBasicBlocks += result.basicBlocks;

		auto& LA = AM.getResult<LoopAnalysis>(F);
		auto& LAM = AM.getResult<LoopAnalysisManagerFunctionProxy>(F).getManager();

		auto& AA = AM.getResult<AAManager>(F);
		auto& AC = AM.getResult<AssumptionAnalysis>(F);
		auto& DT = AM.getResult<DominatorTreeAnalysis>(F);
		auto& SE = AM.getResult<ScalarEvolutionAnalysis>(F);
		auto& TLI = AM.getResult<TargetLibraryAnalysis>(F);
		auto& TTI = AM.getResult<TargetIRAnalysis>(F);

		LoopStandardAnalysisResults AR = { AA , AC, DT, LA, SE, TLI, TTI, nullptr, nullptr };

		for (auto& L : LA) {
			handleLoop(L, LAM, AR);
		}

		return PreservedAnalyses::all();
	}







};

