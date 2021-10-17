//===-- ch2ohCount.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/ch2ohCount/ch2ohCount.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

#define DEBUG_TYPE "ch2ohCount"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(BB_count, "BasicBlocks amount");
ALWAYS_ENABLED_STATISTIC(OPS_count, "Math operations amount");
ALWAYS_ENABLED_STATISTIC(loops_count, "Loops amount");

PreservedAnalyses Ch2ohCountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

    for (auto BB = F.begin(); BB != F.end(); ++BB) ++BB_count;

    for (const auto& I : instructions(F)) {
        switch (I.getOpcode()) {
            case Instruction::Add:
            case Instruction::FAdd:
            case Instruction::Sub:
            case Instruction::FSub:
            case Instruction::Mul:
            case Instruction::FMul:
            case Instruction::FDiv:
            case Instruction::SDiv:
            case Instruction::UDiv:
                ++OPS_count;
        }
    }

    auto& LA = AM.getResult<LoopAnalysis>(F);
    for (auto& L : LA) ++loops_count;

    errs() << "BasicBlocks: " << BB_count << "\n"
            << "Math instructions: " << OPS_count << "\n" 
            << "Loops: " << loops_count << "\n";

    return PreservedAnalyses::all();
}