#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm {
    class MoiseevPass3 : public PassInfoMixin<MoiseevPass3> {
    public:
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        static bool isRequired() { return true; } 
    };
}