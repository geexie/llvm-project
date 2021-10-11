#include "llvm/Transforms/AlexgivingCount/AlexgivingCount.h"

#define DEBUG_TYPE "AlexgivingCount"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"

 using namespace llvm;
 PreservedAnalyses AlexgivingPass::run(Function &F,
                                       FunctionAnalysisManager &AM) {

    errs() << "functions " << F.getName() << "\n";

    int BB_count = 0;
    int IN_count = 0;
    for (auto BB = F.begin(); BB != F.end(); ++BB) {
        BB_count++;

        for (auto& IN : instructions(F)){
            IN_count++;
        }
    }

    errs() << "    Number of base blocks " << BB_count << "\n";
    errs() << "        Number of instructions " << IN_count << "\n";

   return PreservedAnalyses::all();
 }
