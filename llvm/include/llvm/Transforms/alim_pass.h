#pragma once
#ifndef LLVM_TRANSFORMS_COUNTER_H
#define LLVM_TRANSFORMS_COUNTER_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm {

    class alim_pass : public PassInfoMixin<alim_pass> {
    public:
        PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
    };
} // namespace llvm

#endif // LLVM_TRANSFORMS_COUNTER_H