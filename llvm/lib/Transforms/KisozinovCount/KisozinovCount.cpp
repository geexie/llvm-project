#include "llvm/Transforms/KisozinovCount/KisozinovCount.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/ADT/Statistic.h"

#define DEBUG_TYPE "kisozinov-count"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(F_count, "Number of functions");
ALWAYS_ENABLED_STATISTIC(BB_count, "Number of basic blocks ");
ALWAYS_ENABLED_STATISTIC(OPS_count, "Number of arithmetic operations ");
ALWAYS_ENABLED_STATISTIC(L_count, "Number of loops");

PreservedAnalyses KisozinovCountPass::run(Function &F,
                                        FunctionAnalysisManager &AM) {
    F_count++;  // counting functions
    for (auto& BB : F) {
        BB_count++;     // counting basic blocks
        errs() << "functions " << F.getName() << "\n";
        for (auto& I : BB) {
            switch (I.getOpcode()) {
                case Instruction::Add:
                case Instruction::FAdd:
                case Instruction::Mul:
                case Instruction::FDiv:
                case Instruction::SDiv:
                case Instruction::UDiv:
                case Instruction::Sub:
                case Instruction::FSub:
                OPS_count ++;   // counting arithmetic operations
                break;
            }
        }
    }

    auto& LA = AM.getResult<LoopAnalysis>(F);
    for (auto& L : LA) {
        L_count++;
    }

    return PreservedAnalyses::all();
}
