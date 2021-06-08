#ifndef LLVM_ANALYSIS_AKOMYAGINLOOPNALYSIS_H
#define LLVM_ANALYSIS_AKOMYAGINLOOPNALYSIS_H

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include <algorithm>
#include <utility>

namespace llvm {

    class AKomyaginLoopAnalysis : public AnalysisInfoMixin<AKomyaginLoopAnalysis> {
        public:
            static AnalysisKey Key;
            struct Result {int InvUpd = 0;};
            Result run(Loop &L, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LSAR);
            static StringRef name() { return "AKomyaginLoopAnalysis"; }
    };
}

#endif  