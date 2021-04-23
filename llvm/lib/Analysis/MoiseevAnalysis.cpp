#include "llvm/Analysis/MoiseevAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

namespace llvm {

    AnalysisKey MoiseevAnalysis::Key;

    void MoiseevAnalysisInfo::print(raw_ostream &out) const 
    {
        out << "pow: " << pow_num << "\n";
        out << "add: " << add_num << "\n";
        out << "mul: " << mul_num << "\n";
    }

    MoiseevAnalysis::Result MoiseevAnalysis::run(Function& func, FunctionAnalysisManager& AM)
    {
        Result result;
        for (auto BB = func.begin(); BB != func.end(); ++BB)
        {
            for (auto instr = BB->begin(); instr != BB->end(); ++instr)
            {
                if (instr->getOpcode() == Instruction::Add || instr->getOpcode() == Instruction::FAdd)
                    result.add_num++;
                if (instr->getOpcode() == Instruction::Mul || instr->getOpcode() == Instruction::FMul)
                    result.mul_num++;
            }
        }

        for (auto& instr :instructions(func))
        {
            if (auto CI = dyn_cast<CallInst>(&instr))
                if (CI->getCalledFunction()->getName() == "powf")
                    result.pow_num++;
        }
        return result;
    }
}