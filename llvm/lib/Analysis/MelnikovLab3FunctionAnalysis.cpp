#include "llvm/Analysis/MelnikovLab3FunctionAnalysis.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

AnalysisKey MelnikovLab3FunctionAnalysis::Key;

MelnikovLab3FunctionAnalysis::Result MelnikovLab3FunctionAnalysis::run(Function& F, FunctionAnalysisManager& LI) {

    MelnikovLab3FunctionAnalysisInfo FAI;
    // error: no viable conversion from 'ilist_iterator<[2 * ...], true>' to 'ilist_iterator<[2 * ...], false>'
    //  for (Function::iterator bb = F.begin(), last_bb = F.end(); bb != last_bb; ++bb)
/*
    for (Function::iterator bb = F.begin(), last_bb = F.end(); bb != last_bb; ++bb){ 
        FAI.BasicBlockCount++;
        for (BasicBlock::iterator instr = bb->begin(), instr_end = bb->end();  instr != instr_end; ++instr){ 
                
            if (instr->getOpcode() == 14) { // fadd
                FAI.FAddCount++;
            }
            else if (instr->getOpcode() == 18){ // fmul
                FAI.FMullCount++;
            }
        }
    }
*/

    for (const auto &BB : F){ 
        FAI.BasicBlockCount++;
        for (const auto &I : BB){ 
                
            if (I.getOpcode() == 14) { // fadd
                FAI.FAddCount++;
            }
            else if (I.getOpcode() == 18){ // fmul
                FAI.FMullCount++;
            }
        }
    }
    return FAI;
}

  
/*
void MelnikovLab3FunctionAnalysisInfo::print(raw_ostream &OS) const {
  OS << "BasicBlockCount: " << BasicBlockCount << "\n"
     << "FAddCount: " << FAddCount << "\n"
     << "FMullCount: " << FMullCount << "\n";
}

MelnikovLab3FunctionAnalysisInfo
MelnikovLab3FunctionAnalysis::run(Function &F, FunctionAnalysisManager &FAM) {
  return MelnikovLab3FunctionAnalysisInfo::getMelnikovLab3FunctionAnalysisInfo(
      F, FAM.getResult<LoopAnalysis>(F));
}

PreservedAnalyses
MelnikovLab3FunctionAnalysisPrinter::run(Function &F, FunctionAnalysisManager &AM) {
  OS << "Printing analysis results of CFA for function "
     << "'" << F.getName() << "':"
     << "\n";
  AM.getResult<MelnikovLab3FunctionAnalysis>(F).print(OS);
  return PreservedAnalyses::all();
}

*/