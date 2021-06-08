#include "llvm/Analysis/VokhmyaninaAnalysis.h"

namespace llvm {

AnalysisKey VokhmyaninaAnalysis::Key;

void VokhmyaninaAnalysisInfo::print(raw_ostream &out) const {
    out << "----------------" << "\n"
       << "Total pow: " << total_pow << "\n"
       << "Total add: " << total_add << "\n"
       << "Total mul: " << total_mul << "\n";
}

VokhmyaninaAnalysis::Result VokhmyaninaAnalysis::run(Function& F, FunctionAnalysisManager & AM) {
    Result res;

    for (auto B = F.begin(); B != F.end(); ++B) {
        for (auto I = B->begin() ; I != B->end(); ++I) {
            if (I->getOpcode() == Instruction::Add || I->getOpcode() == Instruction::FAdd) { res.total_add++;}
            else if (I->getOpcode() == Instruction::Mul || I->getOpcode() == Instruction::FMul) { res.total_mul++;}
            else if (auto CI = dyn_cast<CallInst>(I)) {
                if(CI->getCalledFunction()->getName() == "powf") { res.total_pow++; }
            }
        }
    }
    return res;
}

}
