//===-- KlykovCount.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/KlykovCount/KlykovCount.h"

#define DEBUG_TYPE "klykov-count"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

PreservedAnalyses KlykovCountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << "functions " << F.getName() << "\n";
  return PreservedAnalyses::all();
}
