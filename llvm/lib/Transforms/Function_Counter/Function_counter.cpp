#include "llvm/Transforms/Function_Counter/Function_counter.h"

#define DEBUG_TYPE "Function_counter"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(Fun_num, "Number of functions");
ALWAYS_ENABLED_STATISTIC(arithm_OPS_Num, "Number of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(BB_num, "Number of BasicBlocks");

PreservedAnalyses Function_counter_pass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
    Fun_num ++;
    for (auto& BB : F) {
        BB_num++;
        for (auto& IN : instructions(F)){
            arithm_OPS_Num++;
        }
    }

    errs() << "Number of Func " << Fun_num << "\n";
    errs() << "Number of BB " << BB_num << "\n";
    errs() << "Number of OPS " << arithm_OPS_Num << "\n";

   return PreservedAnalyses::all();
}