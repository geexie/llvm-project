#include "llvm/Transforms/shaidiPass/shaidiPass.h"

#define DEBUG_TYPE "shaidiPass"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(F_count, "Number of functions");
ALWAYS_ENABLED_STATISTIC(OPS_count, "Number of BB ");
ALWAYS_ENABLED_STATISTIC(BB_count, "Number of OPS ");


PreservedAnalyses shaidiPass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
    F_count ++;
    for (auto BB = F.begin(); BB != F.end(); ++BB) {
        BB_count++;
        for (auto IN = BB->begin(); IN != BB->end(); ++IN){
            OPS_count++;
        }
    }

    errs() << "Number of Func " << F_count << "\n";
    errs() << "    Number of BB " << BB_count << "\n";
    errs() << "        Number of OPS " << OPS_count << "\n";

    return PreservedAnalyses::all();
}