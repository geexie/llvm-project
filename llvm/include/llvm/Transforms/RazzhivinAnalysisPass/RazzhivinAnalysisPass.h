#pragma once

#include "llvm/IR/PassManager.h"

namespace llvm {
    class RazzhivinAnalysisPass : public PassInfoMixin<RazzhivinAnalysisPass> {
        PreservedAnalyses run(Function& func, FunctionAnalysisManager& AM);
        static bool isRequired() { return true; }
    };
} 