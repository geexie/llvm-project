#pragma once

#include "llvm/Analysis/RazzhivinAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"


namespace llvm {
    AnalysisKey RazzhivinAnalysis::Key;
    void RazzhivinAnalysisInfo::print(raw_ostream &OS) const {
        OS << "Num of adds: " << adds << "\n"; //std::endl;
        OS << "Num of muls: " << muls << "\n"; //std::endl;
        OS << "Num of powfs: " << powfs << "\n"; //std::endl;
        return;
    }

    RazzhivinAnalysis::Result RazzhivinAnalysis::run(Function& func, FunctionAnalysisManager& AM){
        Result res;
        for (auto baseBlock = func.begin(); baseBlock != func.end(); ++baseBlock){
            for (auto instr = baseBlock->begin(); instr != baseBlock->end(); ++instr){
                if (instr->getOpcode() == Instruction::Add || instr->getOpcode() == Instruction::FAdd)
                    res.adds++;
                if (instr->getOpcode() == Instruction::Mul || instr->getOpcode() == Instruction::FMul)
                    res.muls++;
            }
        }

        for (auto& instr :instructions(func)){
            if (auto callInst = dyn_cast<CallInst>(&instr))
                if (callInst->getCalledFunction()->getName() == "powf")
                    res.powfs++;
        }
        return res;
    }
} 