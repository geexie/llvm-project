//===-- ch2ohCount.h - Example Transformations ------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_CH2OHCOUNT_CH2OHCOUNT_H
#define LLVM_TRANSFORMS_CH2OHCOUNT_CH2OHCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LPMUpdater;

class Ch2ohCountPass : public PassInfoMixin<Ch2ohCountPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_CH2OHCOUNT_CH2OHCOUNT_H 