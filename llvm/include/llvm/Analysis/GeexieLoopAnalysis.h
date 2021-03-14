//=- GeexieLoopAnalysis.h - Toy Loop Analysis --*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_ANALYSIS_GEEXIE_LOOPANALYSIS_H
#define LLVM_ANALYSIS_GEEXIE_LOOPANALYSIS_H

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopAnalysisManager.h"

namespace llvm {

class GeexieLoopAnalysis : public AnalysisInfoMixin<GeexieLoopAnalysis> {
public:
  static AnalysisKey Key;
  struct Result {
    int64_t InvUpdatesCount = 0;
  };

  Result run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA);

  static StringRef name() { return "GeexieLoopAnalysis"; }
};

} // namespace llvm
#endif // LLVM_ANALYSIS_GEEXIE_LOOPANALYSIS_H
