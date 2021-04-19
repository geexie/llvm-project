#ifndef LLVVM_TRANSFORMS_KORKUNOVTRANSANALYSISPASS_KORKUNOVTRANSANALYSISPASS_H
#define LLVVM_TRANSFORMS_KORKUNOVTRANSANALYSISPASS_KORKUNOVTRANSANALYSISPASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopAnalysisManager.h"

namespace llvm{

    class LPMUpdater;

    class KorkunovTransAnalysisPass : public PassInfoMixin<KorkunovTransAnalysisPass>{
        public:
            PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
            void iterateOnLoops(llvm::Loop &L, llvm::LoopAnalysisManager &LAM, llvm::LoopStandardAnalysisResults &LSAR);
    };

}

#endif