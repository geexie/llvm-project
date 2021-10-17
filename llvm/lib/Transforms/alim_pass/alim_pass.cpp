#include "llvm/Transforms/alim_pass/alim_pass.h"

#define DEBUG_TYPE "alim_pass"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(F_num, "Number of Functions");
ALWAYS_ENABLED_STATISTIC(OPS_num, "Number of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(BB_num, "Number of BasicBlocks");
ALWAYS_ENABLED_STATISTIC(L_num, "Number of Loops");

PreservedAnalyses alim_pass::run(Function& F, FunctionAnalysisManager& AM) {
    F_num++;
    auto& LA = AM.getResult<LoopAnalysis>(F);
    for (auto& loop : LA) {
        L_num++;
    }
    for (auto& BB : F) {
        BB_num++;
        for (auto& IN : instructions(F)) {
            OPS_num++;
        }
    }

    errs() << "Number of F " << F_num << "\n";
    errs() << "Number of BB " << BB_num << "\n";
    errs() << "Number of OPS " << OPS_num << "\n";
    errs() << "Number of L " << L_num << "\n";

    return PreservedAnalyses::all();
}