#include "llvm/Transforms/AsmaCount/AsmaCount.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

#define DEBUG_TYPE "asma-count"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(BB_count, "BasicBlocks amount");
ALWAYS_ENABLED_STATISTIC(OPS_count, "Math operations amount");
ALWAYS_ENABLED_STATISTIC(loops_count, "Loops amount");

PreservedAnalyses AsmaCountPass::run(Function &F,
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