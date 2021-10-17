//===-- PaninaPCount.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/PaninaPCount/PaninaPCount.h"

#define DEBUG_TYPE "paninap-count"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(fun_count, "Number of functions");
ALWAYS_ENABLED_STATISTIC(ops_count, "Number of arithmetic operations");
ALWAYS_ENABLED_STATISTIC(bb_count, "Number of basic blocks");
ALWAYS_ENABLED_STATISTIC(loop_count, "Number of loops");

PreservedAnalyses PaninaPCountPass::run(Function &F, FunctionAnalysisManager &AM) {

  fun_count +=1;

  for (auto BB = F.begin(); BB != F.end(); ++BB) {
    bb_count +=1;

  for (auto I = BB->begin(); I != BB->end(); ++I) {
    switch (I->getOpcode()) {
      case Instruction::Add:
      case Instruction::FAdd:
      case Instruction::Sub:
      case Instruction::FSub:
      case Instruction::Mul:
      case Instruction::FMul:
      case Instruction::FDiv:
      case Instruction::SDiv:
      case Instruction::UDiv:
        ops_count += 1;
    }
  }
  
  auto& LA = AM.getResult<LoopAnalysis>(F);
  for (auto& L : LA) {
    loop_count += 1;
  }
}

  errs() << "Number of functions" << fun_count << "\n"
         << "Number of arithmetic operations" << ops_count << "\n"
         << "Number of basic blocks" << bb_count << "\n";
	 << "Number of loops" << loop_count << "\n";

  return PreservedAnalyses::all();
}