#include "llvm/Analysis/BogoroditskayaFunctionAnalysis.h"

#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

AnalysisKey BogoroditskayaFunctionAnalysis::Key;

BogoroditskayaFunctionAnalysis::Result BogoroditskayaFunctionAnalysis::run(Function &F, FunctionAnalysisManager &AM)  
{
    Result result;
    for (Function::iterator i = F.begin(), i_e = F.end(); i != i_e; ++i)              
        {                                                                
        for ( BasicBlock::iterator j = i->begin(), j_end = i->end(); j != j_end; ++j)      
        {
            std::string temp = j->getOpcodeName();
            if (temp == "fadd" || temp == "add")
            {
                result.Num_Add++;
            }
            if (temp == "fmul" || temp == "mul")
            {
                result.Num_Mull++;
            }
        }
    }
    

    for (auto& I : instructions(F)) 
    {
        if (auto C = dyn_cast<CallInst>(&I))
        {
            if(C->getCalledFunction()->getName() == "powf") 
            {
                result.Num_Pow++;
            }
        }
    }
    return result;
}

void BogoroditskayaFunctionAnalysisInfo::print(raw_ostream &OS) const 
{
  OS << "Number of adds : " << Num_Add << "\n"
     << "Number of mulls : " << Num_Mull << "\n"
     << "Number of pows: " << Num_Pow << "\n\n";
}