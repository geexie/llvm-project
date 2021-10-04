#include "llvm/Transforms/NikDemoShowCount/NikDemoShowCount.h"

#define DEBUG_TYPE "NikDemoShowCount"
#include "llvm/ADT/Statistic.h"

using namespace llvm;
PreservedAnalyses NikDemoShowPass::run(Function &F,
FunctionAnalysisManager &AM) {
  errs() << "functions " << F.getName() << "\n";
  return PreservedAnalyses::all();
}
