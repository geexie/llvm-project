#include "llvm/Transforms/ZagoskinVA/GeexieCount.h"
#define DEBUG_TYPE "geexie-count"
#include "llvm/ADT/Statistic.h"
using namespace llvm;
PreservedAnalyses GeexieCountPass::run(Function &F, FunctionAnalysisManager &AM){
	errs() << "functions" << F.getName() << "\n";
	return PreservedAnalyses::all();
}