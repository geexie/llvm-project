//===— GeexieCount.h - Example Transformations —----------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_POLLYLLYZHCOUNT_POLLYLLYZHCOUNT_H
#define LLVM_TRANSFORMS_POLLYLLYZHCOUNT_POLLYLLYZHCOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm {

 class LPMUpdater;
 
class PollyllyZhCountPass : public PassInfoMixin<PollyllyZhCountPass> {
public:
PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} //namespace llvm

#endif // LLVM_TRANSFORMS_POLLYLLYZHCOUNT_POLLYLLYZHCOUNT_H 
