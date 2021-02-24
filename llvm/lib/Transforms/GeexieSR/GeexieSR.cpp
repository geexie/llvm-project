//===-- GeexieSR.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/GeexieSR/GeexieSR.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IRBuilder.h"

#define DEBUG_TYPE "geexie-sr"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

// Example pass which makes strength reduction y = powf(x, 2.f) -> y = x * x
PreservedAnalyses GeexieSRPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  auto pa = PreservedAnalyses::all();

  // iterate over instructions to find candidates
  SmallVector<CallBase*, 16> work_set;
  for (auto& I : instructions(F)) {
    if (auto Call = dyn_cast<CallBase>(&I)) {
      if (Call->isNoBuiltin()) continue;

      const Function *Callee = Call->getCalledFunction();
      if (Callee->getIntrinsicID() == Intrinsic::pow) {
        if (auto RHSC = dyn_cast<ConstantFP>(Call->getOperand(1))) {
          if (RHSC->getValue().convertToFloat() == 2.f) {
            work_set.push_back(Call);
          }
        }
      }
    }
  }

  // replace call instruction to newly created multiply
  while (!work_set.empty()) {
    auto Call = work_set.pop_back_val();
    IRBuilder<> Builder(Call);
    auto base = Call->getOperand(0);
    auto mull = Builder.CreateFMul(base, base, "my_pow2");
    Call->replaceAllUsesWith(mull);
    Call->eraseFromParent();
  }

  // preserve analysis iff none of instruction is removed
  return pa;
}
