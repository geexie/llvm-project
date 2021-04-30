#include "llvm/Analysis/PAZamelinAnalysis.h"

#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"

namespace llvm 
{
    AnalysisKey PAZamelinAnalysis::Key = {};

	PAZamelinAnalysis::Result PAZamelinAnalysis::run(Function& F, FunctionAnalysisManager& AM)
    {
		Result result;

		for (const BasicBlock& B : F)
        {
            for (const Instruction& I : B)
            {
                if (I.isBinaryOp())
                {
                    const auto opcode = I.getOpcode();  
                    switch (opcode)
                    {
                        case Instruction::Add:
                        case Instruction::FAdd:
                        {
                            result.totalAdd++;    
                            break;
                        }                    
                        case Instruction::Mul:
                        case Instruction::FMul:
                        {
                            result.totalMul++;
                            break;
                        }
                        default:
                            break;
                    }
                }
                else if (const auto* call = dyn_cast<CallBase>(&I))
                {
                    const StringRef& name = call->getCalledFunction()->getName();
                   	if(name == "pow" or name == "powf")
        	        {
                        result.totalPow++;
                    }                            
                }
            }
        }

		return result;
	}

	void PAZamelinAnalysisInfo::print(raw_ostream& ostream) const
    {
		ostream << totalAdd << " - Number of add instructions" << "\n"
			    << totalMul << " - Number of mul instructions" << "\n"
			    << totalPow << " - Number of pow and powf instructions" << "\n"; 
	}
} 