//===-- GeexiePhi.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/GeexiePhi/GeexiePhi.h"

#include "llvm/IR/InstIterator.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/IntrinsicInst.h"

#define DEBUG_TYPE "geexie_phi"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

STATISTIC(TotalPhis, "Number of Phi instructions");

PreservedAnalyses GeexiePhiPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  for (auto& I : instructions(F)) {
    if (isa<PHINode>(&I)) {
      TotalPhis++;
    }

    if (auto PN = dyn_cast<PHINode>(&I)) {
      errs() << *PN;
      int numArgs = PN->getNumIncomingValues();
      errs() << " ‐ has " << numArgs << " incoming values\n";
      for (auto arg = 0; arg < numArgs; arg++) {
        errs() << arg << " : " << PN->getIncomingBlock(arg)->getName() <<"\n";
      }
    }
  }

  auto pa = PreservedAnalyses::all();
  SmallVector<PHINode*, 16> kill;
  // for (auto& BB : F.getBasicBlockList()) {
  for (auto BB = F.begin(); BB != F.end(); ++BB) {
    // phi node is always the first instruction in Basic Block
    auto I = BB->begin();
    if (auto PN = dyn_cast<PHINode>(&*I)) {
      if (PN->hasConstantValue()) {
        pa = PreservedAnalyses::none();
        kill.push_back(PN);
      }
    }
  }

  while (!kill.empty()) {
    auto PN = kill.pop_back_val();
    PN->replaceAllUsesWith(PN->getIncomingValue(0));
    PN->eraseFromParent();
  }

  return pa;
}
