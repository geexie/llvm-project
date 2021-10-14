#include "llvm/Transforms/AlexgivingCount/AlexgivingCount.h"

#define DEBUG_TYPE "AlexgivingCount"

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(F_count, "Number of functions");
ALWAYS_ENABLED_STATISTIC(OPS_count, "Number of BB ");
ALWAYS_ENABLED_STATISTIC(BB_count, "Number of OPS ");
ALWAYS_ENABLED_STATISTIC(LOOP_Count, "Number of Loops ");


PreservedAnalyses AlexgivingPass::run(Function &F, FunctionAnalysisManager &AM) {
    F_count ++;

    for (__attribute__((unused)) auto& L : AM.getResult<LoopAnalysis>(F)) {
        ++LOOP_Count;
    }

    for (auto& BB : F) {
        BB_count++;

        for (__attribute__((unused)) auto& IN : BB) {
            OPS_count++;
        }
    }

    errs() << "Number of Func " << F_count << "\n";
    errs() << "    Number of BB " << BB_count << "\n";
    errs() << "        Number of OPS " << OPS_count << "\n";
    errs() << "            Number of Loops " << LOOP_Count << "\n";

   return PreservedAnalyses::all();
}
