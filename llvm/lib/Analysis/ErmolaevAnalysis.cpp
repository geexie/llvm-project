#include "llvm/Analysis/ErmolaevAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

namespace llvm {

    AnalysisKey ErmolaevAnalysis::Key;

    void ErmolaevAnalysisInfo::print(raw_ostream &out) const 
    {
        out << "pow: " << powNum << "\n";
        out << "add: " << addNum << "\n";
        out << "mul: " << mulNum << "\n";
    }

    ErmolaevAnalysis::Result ErmolaevAnalysis::run(Function& func, FunctionAnalysisManager& AM)
    {
        Result result;
        for (auto BB = func.begin(); BB != func.end(); ++BB)
        {
            for (auto instr = BB->begin(); instr != BB->end(); ++instr)
            {
                if (instr->getOpcode() == Instruction::Add || instr->getOpcode() == Instruction::FAdd){
                    result.addNum++;
				}
                if (instr->getOpcode() == Instruction::Mul || instr->getOpcode() == Instruction::FMul){
                    result.mulNum++;
				}
            }
        }

        for (auto& instr :instructions(func))
        {
            if (auto CI = dyn_cast<CallInst>(&instr)){
                if (CI->getCalledFunction()->getName() == "powf"){
                    result.powNum++;
				}
			}
        }
        return result;
    }
}