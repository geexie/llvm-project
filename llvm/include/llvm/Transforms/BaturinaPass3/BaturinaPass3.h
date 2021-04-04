#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm {

class BaturinaPass3 : public PassInfoMixin<BaturinaPass3> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
    static bool isRequired() { 
        return true; 
    } 
};

}