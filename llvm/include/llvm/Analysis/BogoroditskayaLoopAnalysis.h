#ifndef LLVM_BOGORODITSKAYALOOPANALYSIS_H_
#define LLVM_BOGORODITSKAYALOOPANALYSIS_H_

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopAnalysisManager.h"

namespace llvm{

    class BogoroditskayaLoopAnalysis : public AnalysisInfoMixin<BogoroditskayaLoopAnalysis>{
    public:
        static AnalysisKey Key;
        struct Result {
            int64_t InvUpdatesCount = 0;
    };

    Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA);

    static StringRef name() { return "BogoroditskayaLoopAnalysis";}
};

} // namespace llvm
#endif // LLVM_BOGORODITSKAYALOOPANALYSIS_H_