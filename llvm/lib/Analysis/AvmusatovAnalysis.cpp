#include "llvm/Analysis/AvmusatovAnalysis.h"

namespace llvm {

    AnalysisKey AvmusatovAnalysis::Key;

    AvmusatovAnalysis::Result AvmusatovAnalysis::run(Function& F, FunctionAnalysisManager& FAM) {
        Result result;

        for (BasicBlock& BB : F) {
            for (Instruction& instr : BB) {
                result.basicBlockCount++;

                if (auto BO = dyn_cast<BinaryOperator>(&instr)) {
                    auto opCode = BO->getOpcode();
                    if (opCode == Instruction::Add || opCode == Instruction::FAdd) {
                        result.addOperationCount++;
                    }
                    else if (opCode == Instruction::Mul || opCode == Instruction::FMul) {
                        result.mulOperationCount++;
                    }
                }

                if (auto CI = dyn_cast<CallInst>(&instr)) {
                    if (CI->getCalledFunction()->getName() == "powf") {
                        result.powOperationCount++;
                    }
                }
            }
        }

        return result;
    }


    void AvmusatovAnalysisInfo::printResults(raw_ostream& ostream) const {
        ostream << "Power operations: " << powOperationCount << "\n"
            << "Add operations: " << addOperationCount << "\n"
            << "Mul operations: " << mulOperationCount << "\n"
            << "Basic blocks: " << basicBlockCount << "\n"
            << "\n";
    }
}
