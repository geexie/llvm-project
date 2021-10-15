#include "llvm/Transforms/Golovanov_CTR/Golovanov_CTR.h"

#define DEBUG_TYPE "Golovanov_CTR"
#include "llvm/IR/InstIterator.h"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(Functions_number, "Number of functions");
ALWAYS_ENABLED_STATISTIC(Operations_number, "Number of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(BasicBlocks_number, "Number of BasicBlocks");
ALWAYS_ENABLED_STATISTIC(Loops_number, "Number of loops");

PreservedAnalyses Golovanov_CTR_pass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
    Functions_number ++;
    auto& LA = AM.getResult<LoopAnalysis>(F);
    for (auto& loop: LA){
        Loops_number++;
    }
    for (auto& BB : F) {
        BasicBlocks_number++;
        for (auto& IN : instructions(F)){
            Operations_number++;
        }
    }

    errs() << "Number of Functions " << Functions_number << "\n";
    errs() << "Number of Operations " << Operations_number << "\n";
	errs() << "Number of BasicBlocks " << BasicBlocks_number << "\n";
    errs() << "Number of Loops " << Loops_number << "\n";

   return PreservedAnalyses::all();
}
