//===-- HelloWorld.h - Example Transformations ------------------*- C++ -*-===//
//
//  The pass counting only function definitions, loops, Basic blocks, Arithmetic instructions of type add and mull.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_AVMUSATOVCOUNT_AVMUSATOVCOUNT_H
#define LLVM_TRANSFORMS_AVMUSATOVCOUNT_AVMUSATOVCOUNT_H

#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"

namespace llvm {

  class AvmusatovCount : public PassInfoMixin<AvmusatovCount> {
  public:
    PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
    static bool isRequired() { return true; }
  };
} // namespace llvm
#endif //LLVM_TRANSFORMS_AVMUSATOVCOUNT_AVMUSATOVCOUNT_H