#include "llvm/Transforms/KisozinovCount/KisozinovCount.h"

#define DEBUG_TYPE "kisozinov-count"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

PreservedAnalyses KisozinovCountPass::run(Function &F,
                                        FunctionAnalysisManager &AM) {
    errs() << "functions" << F.getName() << "\n";
    return PreservedAnalyses::all();
}
