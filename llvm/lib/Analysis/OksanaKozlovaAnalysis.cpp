#include "llvm/Analysis/OksanaKozlovaAnalysis.h"

using namespace llvm;

AnalysisKey OksanaKozlovaAnalysis::Key;

OksanaKozlovaAnalysis::Result OksanaKozlovaAnalysis::run(Function& F, FunctionAnalysisManager & FAM) {
    
    Result result;

    if (!F.isDeclaration()) {
        result.totalFuncs++;
    }

    for (auto B = F.begin(); B != F.end(); ++B) {
        result.totalBasicBlocks++;
        for (auto I = B->begin(); I != B->end(); ++I) {
            std::string instr = std::string(I->getOpcodeName());
            if (instr == "add" || instr == "fadd" || instr == "mul" || instr == "fmul") {
                result.totalArithmInstrs++;
            }
        }
    }
    return result;

}


void OksanaKozlovaAnalysisInfo::print(raw_ostream &ostream) const {
    ostream << "Total Functions =: " << totalFuncs << "\n"
       << "Total Arithmetic Instructions =: " << totalArithmInstrs << "\n"
       << "Total Basic Blocks =: " << totalBasicBlocks << "\n";
} 