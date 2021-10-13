#include "llvm/Transforms/MyCount/MyCount.h"

#define DEBUG_TYPE "MyCount"
#include "llvm/ADT/Statistic.h"

using namespace llvm;
PreservedAnalyses NikDemoShowPass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
  errs() << "functions " << F.getName() << "\n";
  return PreservedAnalyses::all();
}