#ifndef LLVM_ANALYSIS_SELIVANOVSKAYAANALYSIS_H
#define LLVM_ANALYSIS_SELIVANOVSKAYAANALYSIS_H


#include "llvm/Analysis/LoopInfo.h"

using namespace std;


namespace llvm {

class SelivanovskayaAnalysisInfo {
public:
    void print(raw_ostream &ostream) const;
    int64_t Adds = 0;
    int64_t Muls = 0;
    int64_t Pows = 0;
};

class SelivanovskayaAnalysis : public AnalysisInfoMixin<SelivanovskayaAnalysis> {
public:
    static AnalysisKey Key;
    using Result = SelivanovskayaAnalysisInfo;

    Result run(Function& F, FunctionAnalysisManager& FAM);
};

} // namespace llvm  

#endif