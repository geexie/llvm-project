#include "llvm/Transforms/BogomazovCount/BogomazovCount.h"


#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/LoopInfo.h"

#define DEBUG_TYPE "BogomazovCount"

 using namespace llvm;

ALWAYS_ENABLED_STATISTIC(F_count, "Number of functions");
ALWAYS_ENABLED_STATISTIC(BB_count, "BB amount");
ALWAYS_ENABLED_STATISTIC(OPS_count, "OPS amount");
ALWAYS_ENABLED_STATISTIC(loops_count, "Loops amount");


PreservedAnalyses BogomazovCountPass::run(Function &F, FunctionAnalysisManager &AM) {
    F_count ++;

    for (auto BB = F.begin(); BB != F.end(); ++BB) {
        BB_count += 1;
        for (auto I = BB->begin(); I != BB->end(); ++I) {
            switch (I->getOpcode()) {
                case Instruction::Add:
                    OPS_count += 1;
                    break;
                case Instruction::FAdd:
                    OPS_count += 1;
                    break;
                case Instruction::Mul:
                    OPS_count += 1;
                    break;
                case Instruction::FDiv:
                    OPS_count += 1;
                    break;
                case Instruction::SDiv:
                    OPS_count += 1;
                    break;
                case Instruction::UDiv:
                    OPS_count += 1;
                    break;
                case Instruction::Sub:
                    OPS_count += 1;
                    break;
                case Instruction::FSub:
                    OPS_count += 1;
                    break;
        }
        }
    }

    auto& LA = AM.getResult<LoopAnalysis>(F);
    for (auto& L : LA) ++loops_count;

    errs() << "Functions: " << F_count << "\n"
           << "BB: " << BB_count << "\n"
           << "OPS: " << OPS_count << "\n"
           << "Loops: " << loops_count << "\n";

   return PreservedAnalyses::all();
}