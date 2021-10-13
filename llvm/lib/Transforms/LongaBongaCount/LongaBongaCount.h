#ifndef LLVM_TRANSFORMS_LONGABONGA_COUNT_H
 #define LLVM_TRANSFORMS_LONGABONGA_COUNT_H

 #include "llvm/IR/PassManager.h"

 namespace llvm {

     class LongaBongaPass : public PassInfoMixin<LongaBongaPass> {
         public:
             PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
         };
 } // namespace llvm

 #endif // LLVM_TRANSFORMS_LONGABONGA_COUNT_H