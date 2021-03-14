//===- GeexieLoopAnalysis.cpp - Toy Loop Analysis ------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Analysis/GeexieLoopAnalysis.h"
#include "llvm/IR/Instructions.h"

#include "llvm/IR/InstIterator.h" // for instructions(F)
#include "llvm/Analysis/LoopInfo.h"

#include <set>

using namespace llvm;

AnalysisKey GeexieLoopAnalysis::Key;

GeexieLoopAnalysis::Result GeexieLoopAnalysis::run(Loop& L,
                            LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA) {
  // no updates to induction variable in a loop or it's not in a canonical form
  int64_t InvUpdatesCount = -1;

  // check if induction variable is in a canonical form
  if (PHINode* indVar = L.getCanonicalInductionVariable()) {
    // collect all binary operators which update this induction variable
    // in ideal vectorizable case it should be a single binary operator which updates loop induction
    SmallVector<BinaryOperator*, 16> updates;
    for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
      if (auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
        if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar) {
          updates.push_back(binOp);
        }
      }
    }
    InvUpdatesCount = updates.size();
    // errs() << *indVar << "is updated " << updates.size() << "times\n";
  }
  Result res = {InvUpdatesCount};
  return res;
}
