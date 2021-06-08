#ifndef LLVM_TRANSFORMS_SDANILOV_COUNTING_PASS
#define LLVM_TRANSFORMS_SDANILOV_COUNTING_PASS

#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"

namespace llvm {
    class SdanilovPass : public PassInfoMixin<SdanilovPass> {
    public:
        void countLoopsNested(Loop* loop);
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
        static bool isRequired(){return true;};
    };
}
#endif
