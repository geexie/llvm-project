#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm {

    class AvmusatovPass : public PassInfoMixin<AvmusatovPass> {
    public:
        PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
        static bool isRequired() { return true; }
    };
}