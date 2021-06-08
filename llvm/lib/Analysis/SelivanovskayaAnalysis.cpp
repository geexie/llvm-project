#include "llvm/Analysis/SelivanovskayaAnalysis.h"

namespace llvm {

AnalysisKey SelivanovskayaAnalysis::Key;

void SelivanovskayaAnalysisInfo::print(raw_ostream &ostream) const {
    ostream << "Pows - " << Pows << "\n"
       << "Adds - " << Adds << "\n"
       << "Muls - " << Muls << "\n";
}
 
SelivanovskayaAnalysis::Result SelivanovskayaAnalysis::run(Function& F, FunctionAnalysisManager & FAM) {

    Result result;

    for (auto BB = F.begin(); BB != F.end(); ++BB) {
        for (auto INST = BB->begin() ; INST != BB->end(); ++INST) {

            if (INST->getOpcode() == Instruction::Add || INST->getOpcode() == Instruction::FAdd) { 
                result.Adds++;
            }
            else if (INST->getOpcode() == Instruction::Mul || INST->getOpcode() == Instruction::FMul) {
                result.Muls++; 
            }
            else if (auto CI = dyn_cast<CallInst>(INST)) {
                if(CI->getCalledFunction()->getName() == "powf") { 
                    result.Pows++;
                }
            }

        }
    }
    return result;
}

} // namespace llvm
