#pragma once

#include "llvm/IR/PassManager.h"

namespace llvm {
    class VolokhAnalysisPass : public PassInfoMixin<VolokhAnalysisPass> {
        PreservedAnalyses run(Function& func, FunctionAnalysisManager& AM);
        static bool isRequired() { return true; }
    };
}