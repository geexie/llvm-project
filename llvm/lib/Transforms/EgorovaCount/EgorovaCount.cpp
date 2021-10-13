//===-- EgorovaCount.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/EgorovaCount/EgorovaCount.h"

#define DEBUG_TYPE "egorova-count"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(F_count, "Number of functions");
ALWAYS_ENABLED_STATISTIC(OPS_count, "Number of BB ");
ALWAYS_ENABLED_STATISTIC(BB_count, "Number of OPS ");


PreservedAnalyses EgorovaCountPass::run(Function &F,
                                       FunctionAnalysisManager &AM) {
    F_count ++;
    for (auto& BB : F) {
        BB_count++;
        for (auto& IN : instructions(F)){
            OPS_count++;
        }
    }

    errs() << "Number of Func " << F_count << "\n";
    errs() << "    Number of BB " << BB_count << "\n";
    errs() << "        Number of OPS " << OPS_count << "\n";

   return PreservedAnalyses::all();
}