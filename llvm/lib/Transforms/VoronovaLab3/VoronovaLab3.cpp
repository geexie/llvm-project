#include "llvm/Transforms/VoronovaLab3/VoronovaLab3.h"
#include "llvm/Analysis/VoronovaAnalisis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"

#define DEBUG_TYPE "VoronovaLab3"
using namespace llvm;

STATISTIC(CountPows, "Number of pows");
STATISTIC(CountAdds, "Number of adds");
STATISTIC(CountMulls, "Number of mulls");



PreservedAnalyses VoronovaLab3::run(Function& F, FunctionAnalysisManager& AM) 
{

	auto& G = AM.getResult<VoronovaAnalisis>(F);
	CountAdds += G.CountAdds;
	CountMulls += G.CountMulls;
	CountPows += G.CountPows;

	G.output(errs());

	

	return PreservedAnalyses::all();
}