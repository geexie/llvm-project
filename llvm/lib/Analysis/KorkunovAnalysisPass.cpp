#include "llvm/Analysis/KorkunovAnalysisPass.h"

#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LLVMContext.h"

using namespace llvm;

KorkunovAnalysisPassInfo
KorkunovAnalysisPassInfo::getKorkunovAnalysisPassInfo(const Function &F,
                                                  const LoopInfo &LI) {
  KorkunovAnalysisPassInfo FPI;
    for(auto it_BB = F.begin(); it_BB != F.end(); ++it_BB){
        for(auto it_instr = it_BB->begin(); it_instr != it_BB->end(); ++it_instr){
            if(auto ci = dyn_cast<CallBase>(it_instr)){
                if(ci->getCalledFunction()->getName()=="llvm.pow.f32")
                    FPI.tpowf++;
            }
            else{
                auto tmp = it_instr->getOpcodeName();
                if(strcmp(tmp, "fmul" )==0) 
                    FPI.tfmul++;
                else if(strcmp(tmp, "fadd")==0) 
                    FPI.tfadd++;
            }
        }
    }
  return FPI;
}

void KorkunovAnalysisPassInfo::print(raw_ostream &OS) const {
  OS << "total fmul - " << tfmul << "\n"
     << "total fadd - " << tfadd << "\n"
     << "total powf - " << tpowf << "\n\n";
}

AnalysisKey KorkunovAnalysisPass::Key;

KorkunovAnalysisPassInfo
KorkunovAnalysisPass::run(Function &F, FunctionAnalysisManager &FAM) {
  return KorkunovAnalysisPassInfo::getKorkunovAnalysisPassInfo(
      F, FAM.getResult<LoopAnalysis>(F));
}

PreservedAnalyses
KorkunovAnalysisPassPrinter::run(Function &F, FunctionAnalysisManager &AM) {
  OS << "Printing analysis results of CFA for function "
     << "'" << F.getName() << "':"
     << "\n";
  AM.getResult<KorkunovAnalysisPass>(F).print(OS);
  return PreservedAnalyses::all();
}
