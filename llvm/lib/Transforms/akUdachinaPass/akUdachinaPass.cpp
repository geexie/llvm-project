#include "llvm/Transforms/akUdachinaPass/akUdachinaPass.h"
using namespace std;

using namespace llvm;

STATISTIC(TotalDef, "Number of Function definitions");
STATISTIC(TotalLoops, "Number of Loops");
STATISTIC(TotalBlocks, "Number of Basic blocks");
STATISTIC(TotalAdd, "Number of Add instructions");
STATISTIC(TotalMul, "Number of Mul instructions");


void countLoops(llvm::LoopAnalysis::Result& loops) {
    for (Loop::iterator loops = loops_.begin(); loops != loops_.end(); loops++) {
        recLoops(*loops);
    }
}

void recLoops(Loop* loops) {
    TotalLoops++;
    Loop::iterator loops_ = *loops.getSubLoops();
    for (Loop::iterator loops = loops_.begin(); loops != loops_.end(); loops++) {
        recLoops(*loops);
    }
}

void countTotalAdd(std::string instructionName) {
    if (instructionName == "add" || instructionName == "fadd") {
        TotalAdd++;
    }
}

void countTotalMul(std::string instructionName) {
    if (instructionName == "mul" || instructionName == "fmul") {
        TotalMul++;
    }


    PreservedAnalyses akUdachinaPass::run(Function & F, FunctionAnalysisManager & AM) {
        if (!F.isDeclaration()) {
            TotalDef++;
            llvm::LoopAnalysis::Result& loops = AM.getResult<LoopAnalysis>(F);
            countLoops(F);
            for (BasicBlock& BB : F) {
                TotalBlocks++;
                for (Instruction& I : BB) {
                    std::string instructionName = std::string(I.getOpcodeName());
                    countTotalAdd(instructionName);
                    countTotalMul(instructionName);
                }
            }
        }
        return PreservedAnalyses::all();
    }