#ifndef LLVM_TRANSFORMS_KRAYUSHKINACOUNT_KRAYUSHKINACOUNT_H

#define LLVM_TRANSFORMS_KRAYUSHKINACOUNT_KRAYUSHKINACOUNT_H



#include "llvm/IR/PassManager.h"


namespace llvm {



class LPMUpdater;


class KrayushkinaCountPass : public PassInfoMixin<KrayushkinaCountPass> {
 
 public:
  
PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

};



}  // namespace llvm



#endif  // LLVM_TRANSFORMS_KRAYUSHKINACOUNT_KRAYUSHKINACOUNT_H