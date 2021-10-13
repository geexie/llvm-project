#include "llvm/Transforms/AklCount/AklCount.h"

#define DEBUG_TYPE "akl-count"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

PreservedAnalyses AklCountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << "functions " << F.getName() << "\n";
  return PreservedAnalyses::all();
}