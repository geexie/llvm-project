#pragma once

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/IntrinsicInst.h"
#define DEBUG_TYPE "akUdachinaPass2"

using namespace llvm;




namespace llvm {

class akUdachinaPass2 : public PassInfoMixin<akUdachinaPass2> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

  static bool isRequired() { return true; }

};
