//=- GeexieFunctionAnalysis.h - Toy Function Analysis --*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_ANALYSIS_GEEXIE_FUNCTIONANALYSIS_H
#define LLVM_ANALYSIS_GEEXIE_FUNCTIONANALYSIS_H

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
class Function;

class GeexieFunctionAnalysis : public AnalysisInfoMixin<GeexieFunctionAnalysis> {
public:
  static AnalysisKey Key;
  struct Result {
    int64_t BBsCount = 0;
    int64_t LoopsCount = 0;
    int64_t MulAndAddsCount = 0;
    int64_t PhisCount = 0;
  };

  Result run(Function &F, FunctionAnalysisManager &FAM);
};

} // namespace llvm
#endif // LLVM_ANALYSIS_GEEXIE_FUNCTIONANALYSIS_H
