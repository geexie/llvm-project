#ifndef LLVM_AANOSKOVLOOPANALYSIS_H_
#define LLVM_AANOSKOVLOOPANALYSIS_H_

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Utils/LoopUtils.h"


namespace llvm {

class aanoskovLoopAnalysisInfo {
public:
    //static aanoskovLoopAnalysisInfo getCounts(const Function &F);
    int64_t InvUpdatesCount = 0;
};

// Analysis pass
class aanoskovLoopAnalysis
    : public AnalysisInfoMixin<aanoskovLoopAnalysis> {

public:
    static AnalysisKey Key;

    using Result = aanoskovLoopAnalysisInfo;

    Result run(Loop &L, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LSAR);
};

} // namespace llvm
#endif


