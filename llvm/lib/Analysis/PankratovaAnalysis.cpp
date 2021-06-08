#include "llvm/Analysis/PankratovaAnalysis.h"

using namespace llvm;
AnalysisKey PankratovaAnalysis::Key;


PankratovaAnalysis::Result PankratovaAnalysis::run(Function& F, FunctionAnalysisManager & AM) {
    Result result;

    for (BasicBlock &BB : F) {
        result.totalBlocks++;
        for (Instruction &I : BB) {
            std::string instructionName = std::string(I.getOpcodeName());
            if (instructionName == "add" || instructionName == "fadd") {
                result.totalAdd++;
            }
            else if (instructionName == "mul" || instructionName == "fmul") {
                result.totalMul++;
            }
        }
    }
    return result;
}
