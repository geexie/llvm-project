#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

namespace llvm {

class VokhmyaninaLab3 : public PassInfoMixin<VokhmyaninaLab3> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
    static bool isRequired() { return true; } 
};

} // namespace llvm
