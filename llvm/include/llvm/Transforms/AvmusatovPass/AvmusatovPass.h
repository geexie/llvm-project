#pragma once

#define DEBUG_TYPE "AvmusatovCount"

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

STATISTIC(totalAddOperationCount, "Number of add operations");
STATISTIC(totalMulOperationCount, "Number of mul operations");
STATISTIC(totalPowOperationCount, "Number of pow operations");
STATISTIC(totalBasicBlocksCount, "Number of basic blocks");
STATISTIC(totalVectorizableLoopsCount, "Number of vectorizable loops");

namespace llvm {

    class AvmusatovPass : public PassInfoMixin<AvmusatovPass> {
    public:
        PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
        static bool isRequired() { return true; }
    };
}