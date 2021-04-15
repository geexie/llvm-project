#include "llvm/Analysis/BaturinaAnalysis.h"

namespace llvm {

AnalysisKey BaturinaAnalysis::Key;

BaturinaAnalysis::Result BaturinaAnalysis::run(Function& F, FunctionAnalysisManager & FAM) {
    Result result;

    for (auto basicBlock = F.begin(); basicBlock != F.end(); ++basicBlock) {
        for (auto instruction = basicBlock->begin() ; instruction != basicBlock->end(); ++instruction) {
            if (instruction->getOpcode() == Instruction::Add || instruction->getOpcode() == Instruction::FAdd) { 
                result.totalAdd++;
                }
            else if (instruction->getOpcode() == Instruction::Mul || instruction->getOpcode() == Instruction::FMul) { 
                result.totalMul++;
                }
            else if (auto callInst = dyn_cast<CallInst>(instruction)) {
                if(callInst->getCalledFunction()->getName() == "powf") { 
                    result.totalPow++;
                }
            }
        }
    }
    return result;
}

void BaturinaAnalysisInfo::print(raw_ostream &ostream) const {
    ostream << "Total pow: " << totalPow << "\n"
       << "Total add: " << totalAdd << "\n"
       << "Total mul: " << totalMul << "\n";
}
}