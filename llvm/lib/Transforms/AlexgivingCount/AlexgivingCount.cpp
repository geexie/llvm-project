#include "llvm/Transforms/AlexgivingCount/AlexgivingCount.h"

 #define DEBUG_TYPE "AlexgivingCount"
 #include "llvm/ADT/Statistic.h"

 using namespace llvm;
 PreservedAnalyses AlexgivingPass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
   errs() << "functions " << F.getName() << "\n";
   return PreservedAnalyses::all();
 }
