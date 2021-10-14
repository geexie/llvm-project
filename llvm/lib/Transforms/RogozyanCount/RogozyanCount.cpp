#include "llvm/Transforms/RogozyanCount/RogozyanCount.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

#define DEBUG_TYPE "rogozyan-count"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(OP_count, "Math operations Amount");
ALWAYS_ENABLED_STATISTIC(BB_count, "BasicBlocks Amount");
ALWAYS_ENABLED_STATISTIC(Loop_count, "Loops Amount");

PreservedAnalyses RogozyanCountPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

    for (auto BB = F.begin(); BB != F.end(); ++BB) ++BB_count;

    for (const auto& I : instructions(F)) {
        switch (I.getOpcode()) {
            case Instruction::Add:
            case Instruction::Sub:
            case Instruction::FSub:
            case Instruction::FAdd:
            case Instruction::Mul:
            case Instruction::FMul:
            case Instruction::FDiv:
            case Instruction::SDiv:
            case Instruction::UDiv:
                ++OP_count;
        }
    }

    auto& LA = AM.getResult<LoopAnalysis>(F);
    for (auto& L : LA) ++Loop_count;

    errs() << "BasicBlocks: " << BB_count << "\n"
            << "Math operations: " << OP_count << "\n" 
            << "Loops: " << Loop_count << "\n";

    return PreservedAnalyses::all();
}
