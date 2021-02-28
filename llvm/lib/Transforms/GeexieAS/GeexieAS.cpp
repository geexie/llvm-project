//===-- GeexieAS.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/GeexieAS/GeexieAS.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"

#define DEBUG_TYPE "geexie-as"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

// Example pass which makes algebraic simplification y = x + 0.f -> x
// Ex:
// ```
// ; Function Attrs: noinline nounwind ssp uwtable
// define dso_local float @foo(float %x) #0 {
// entry:
//   %add = fadd float %x, 0.000000e+00
//   ret float %add
// }
// ```
PreservedAnalyses GeexieASPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  auto pa = PreservedAnalyses::all();

  // iterate over instructions to find candidates
  SmallVector<BinaryOperator*, 16> wark_set;
  for (auto& I : instructions(F)) {
    if (auto BO = dyn_cast<BinaryOperator>(&I)) {
      if (auto RHSC = dyn_cast<ConstantFP>(BO->getOperand(1))) {
        if (RHSC->getValue().convertToFloat() == 0.f && BO->getOpcode() == Instruction::FAdd) {
          wark_set.push_back(BO);
          pa = PreservedAnalyses::none();
        }
      }
    }
  }

  // remove redundant operations
  // original IR
  // entry:
  //   t0 = x + 0.f
  //   ret t0
  while (!wark_set.empty()) {
    // replace uses of instruction intended to be removed
    auto BO = wark_set.pop_back_val(); // pops `t0 = x + 0.f` instruction
    BO->replaceAllUsesWith(BO->getOperand(0)); // replace all references to `t0 = x + 0.f` with `x`
    // modified IR
    // entry:
    //   t0 = x + 0.f
    //   ret x
    // erase `t0 = x + 0.f` as its result is not used anymore
    BO->eraseFromParent();
    // modified IR
    // entry:
    //   ret x
  }

  // preserve analysis iff none of instruction is removed
  return pa;
}
