#pragma once
#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"

using namespace llvm;

class OksanaKozlovaCountPass : public PassInfoMixin<OksanaKozlovaCountPass> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
    static bool isRequired() { 
        return true; 
    } 
};
