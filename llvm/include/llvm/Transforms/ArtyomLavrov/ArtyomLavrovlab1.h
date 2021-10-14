#ifndef LLVM_TRANSFORMS_ARTYOMLAVROVLAB1_H
#define LLVM_TRANSFORMS_ARTYOMLAVROVLAB1_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class ArtyomLavrovlab1Pass : public PassInfoMixin<ArtyomLavrovlab1Pass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM); };

} // namespace llvm

#endif // LLVM_TRANSFORMS_ARTYOMLAVROVLAB1_H 