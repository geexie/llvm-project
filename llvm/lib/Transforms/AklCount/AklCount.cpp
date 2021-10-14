#include "llvm/Transforms/AklCount/AklCount.h"

#define DEBUG_TYPE "akl-count"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(amount_function, "Amount of functions");
ALWAYS_ENABLED_STATISTIC(amount_base_blocks, "Amount of base blocks");
ALWAYS_ENABLED_STATISTIC(amount_math_operations, "Amount of math operations");
ALWAYS_ENABLED_STATISTIC(amount_loop, "Amount of lopps");

PreservedAnalyses AklCountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

    amount_function++;

    auto& LA = AM.getResult<LoopAnalysis>(F);
    for (auto& L : LA) {
        amount_loop++;
    }

    for (auto& BB : F) {
        amount_base_blocks++;
        for (auto& I : instructions(F)) {
            switch (I.getOpcode()) {
            case Instruction::Add:
                amount_math_operations++;
                break;
            case Instruction::Sub:
                amount_math_operations++;
                break;
            case Instruction::Mul:
                amount_math_operations++;
                break;
            case Instruction::FDiv:
                amount_math_operations++;
                break;
            case Instruction::SDiv:
                amount_math_operations++;
                break;
            case Instruction::UDiv:
                amount_math_operations++;
                break;
            case Instruction::FAdd:
                amount_math_operations++;
                break;
            case Instruction::FSub:
                amount_math_operations++;
                break;
            case Instruction::FMul:
                amount_math_operations++;
                break;
            default:
                break;
            }
        } 
    }

    errs() << "Amount of functions " << amount_function << "\n";
    errs() << "     Amount of base blocks " << amount_base_blocks << "\n";
    errs() << "         Amount of math operations " << amount_math_operations << "\n";
    errs() << "         Amount of lopps " << amount_loop << "\n";
    
    return PreservedAnalyses::all();
}