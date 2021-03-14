//===- GeexieFunctionAnalysis.cpp - Toy Function Analysis ------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Analysis/GeexieFunctionAnalysis.h"
#include "llvm/IR/Instructions.h"

#include "llvm/IR/InstIterator.h" // for instructions(F)
#include "llvm/Analysis/LoopInfo.h"

#include <set>

using namespace llvm;

AnalysisKey GeexieFunctionAnalysis::Key;

static int64_t handleLoop(Loop *L) {
  int64_t LoopsCount = 1;
  for (Loop *SL : L->getSubLoops()) {
    LoopsCount += handleLoop(SL);
  }
  return LoopsCount;
}

GeexieFunctionAnalysis::Result GeexieFunctionAnalysis::run(Function &F, FunctionAnalysisManager &FAM) {
  int64_t BBsCount = 0;
  int64_t LoopsCount = 0;
  int64_t MulAndAddsCount = 0;
  int64_t PhisCount = 0;
  // count basic blocks within a function
  for (const auto& BB : F/*= F.begin(); BB != F.end(); ++BB*/) {
    BBsCount++;
    // count specific instructions within a basic block
    for (const auto& I : BB/*->begin(); I != BB->end(); ++I*/) {
      std::set<decltype(I.getOpcode())> ioi = {Instruction::Add, Instruction::FAdd, Instruction::Mul, Instruction::FMul};
      if (isa<BinaryOperator>(I)) {
        if (!!ioi.count(I.getOpcode())) {
          MulAndAddsCount++;
        }
      }
    }
  }

  // count Phi-nodes over all instructions in a block
  for (auto& I : instructions(F)) {
    if (isa<PHINode>(&I)) {
      PhisCount++;
    }
  }

  // count loops within a function
  auto& LI = FAM.getResult<LoopAnalysis>(F);
  for (auto& L : LI) {
    LoopsCount += handleLoop(L);
  }

  Result res = {BBsCount, LoopsCount, MulAndAddsCount, PhisCount};
  return res;
}
