#include "llvm/Transforms/AvmusatovCount/AvmusatovCount.h"


#define DEBUG_TYPE "AvmusatovCount"

STATISTIC(funcDefCount, "Number of function definitions");
STATISTIC(loopsCount, "Number of loops");
STATISTIC(basicBlocksCount, "Number of basic blocks");
STATISTIC(mulOperationCount, "Number of mul operations");
STATISTIC(addOperationCount, "Number of add operations");

using namespace llvm;

void countOperations(BasicBlock& basicBlock) {
    for (Instruction& instr : basicBlock) {
        std::string opcodeName = std::string(instr.getOpcodeName());

        if (opcodeName == "mul" || opcodeName == "fmul") {
            ++mulOperationCount;
        }
        else if (opcodeName == "add" || opcodeName == "fadd") {
            ++addOperationCount;
        }
    }
}

static void countInnerLoops(Loop* loop) {
    ++loopsCount;
    for (Loop* innerLoop : loop->getSubLoops()) {
        countInnerLoops(innerLoop);
    }
}

PreservedAnalyses AvmusatovCount::run(Function& F, FunctionAnalysisManager& AM) {

    if (!F.isDeclaration()) {
        ++funcDefCount;
    }

    LoopAnalysis::Result& loops = AM.getResult<LoopAnalysis>(F);
    for (Loop* l : loops) {
        countInnerLoops(l);
    }

    for (BasicBlock& basicBlock : F) {
        ++basicBlocksCount;
        countOperations(basicBlock);
    }

    return PreservedAnalyses::all();
}