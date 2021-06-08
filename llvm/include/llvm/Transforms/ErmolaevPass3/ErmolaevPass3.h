#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm {
    class ErmolaevPass3 : public PassInfoMixin<ErmolaevPass3> {
    public:
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        static bool isRequired() { return true; } 
    };
}