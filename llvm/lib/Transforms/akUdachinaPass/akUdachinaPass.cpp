#include "llvm/Transforms/akUdachinaPass/akUdachinaPass.h"
<<<<<<< HEAD

using namespace llvm;


void countLoops(const Loop* L) {
    totalLoops++;
    auto loops = L->getSubLoops();
    for (auto L = loops.begin(); L != loops.end(); L++) {
        countLoops(*L);
    }
}

PreservedAnalyses akUdachinaPass::run(Function &Func, FunctionAnalysisManager &AM) {
    if (!Func.isDeclaration()) {
        totalDef++;
    }
    llvm::LoopAnalysis::Result& loops = AM.getResult<LoopAnalysis>(Func);
    for (auto L = loops.begin(); L != loops.end(); L++) {
        countLoops(*L);
    }
    for (BasicBlock &BB : Func) {
        totalBlocks++;
        for (Instruction &I : BB) {
            std::string instructionName = std::string(I.getOpcodeName());
            if (instructionName == "add" || instructionName == "fadd") {
                totalAdd++;
            }
            else if (instructionName == "mul" || instructionName == "fmul") {
                totalMul++;
            }
        }
    }
    return PreservedAnalyses::all();
}
=======
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
>>>>>>> 55bcae4089c83552e7635dd3ae3e7b0328a63468
