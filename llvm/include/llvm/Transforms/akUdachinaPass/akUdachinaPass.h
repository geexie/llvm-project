#pragma once

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#define DEBUG_TYPE "akUdachinaPass"

using namespace llvm;

namespace {
    struct akUdachinaPass : public PassInfoMixin<akUdachinaPass> {
    public:
        PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
        static bool isRequired() {
            return true;
        }
    }
}