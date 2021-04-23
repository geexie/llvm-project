#pragma once

#include "llvm/IR/PassManager.h"


using namespace llvm;


class DVorobyovAnalysisPass : public PassInfoMixin<DVorobyovAnalysisPass> 
{
public:
	PreservedAnalyses run(Function& F, FunctionAnalysisManager& FAM);
    static bool isRequired() { return true; }
};