#ifndef LLVM_TRANSFORMS_UTILS_SELIVANOVSKAYALAB3_H
#define LLVM_TRANSFORMS_UTILS_SELIVANOVSKAYALAB3_H

#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/IR/PassManager.h"

namespace llvm {

class SelivanovskayaLab3 : public PassInfoMixin<SelivanovskayaLab3> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
    static bool isRequired() { 
        return true; 
    } 
};

} // namespace llvm

#endif 