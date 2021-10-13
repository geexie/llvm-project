//===-- GeexieCount.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/kdash6/kdash6.h"

#define DEBUG_TYPE "kdash6"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(functions_count, "Count of functions");
ALWAYS_ENABLED_STATISTIC(ops_count, "Count of OPS");
ALWAYS_ENABLED_STATISTIC(bb_count, "Count of BB");

PreservedAnalyses kdash6Pass::run(Function &F, FunctionAnalysisManager &AM) {
                                      
  functions_count +=1;
  
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
}
  
  errs() << "Count of functions" << functions_count << "\n"
         << "Count of OPS" << ops_count << "\n"
         << "Count of BB" << bb_count << "\n";
  
  return PreservedAnalyses::all();
}
