#ifndef LLVM_ANALYSIS_AKOMYAGINANALYSIS_H
#define LLVM_ANALYSIS_AKOMYAGINANALYSIS_H

#pragma once

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
#include <algorithm>
#include <utility>

namespace llvm {

    class AKomyaginAnalysisInfo {
    public:
        void print(raw_ostream &OS);
        int64_t totalPow = 0;
        int64_t totalAdd = 0;
        int64_t totalMul = 0;

    };
    class AKomyaginAnalysis : public AnalysisInfoMixin<AKomyaginAnalysis> {
        public:
            static AnalysisKey Key;
            using Result = AKomyaginAnalysisInfo;
            Result run(Function& F, FunctionAnalysisManager& FAM);
    };

}  

#endif 