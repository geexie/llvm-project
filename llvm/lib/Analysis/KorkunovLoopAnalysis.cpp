#include "llvm/Analysis/KorkunovLoopAnalysis.h"

using namespace llvm;

llvm::AnalysisKey KorkunovLoopAnalysis::Key;

 KorkunovLoopAnalysis::Result KorkunovLoopAnalysis::run(Loop &L, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LSAR){
     int InvUpdatesCount = 0;
         if(PHINode* indVar = L.getCanonicalInductionVariable()){
             SmallVector<BinaryOperator*, 16> updates;
             for(unsigned int i = 0; i < indVar->getNumIncomingValues(); ++i){
                 if(auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))){
                    if(binOp->getOperand(0)==indVar || binOp->getOperand(1)==indVar){
                        updates.push_back(binOp);
                    }
                 }
             }
             InvUpdatesCount=updates.size();
         }
     return {InvUpdatesCount};
  }
 llvm::StringRef KorkunovLoopAnalysis::name() { 
      return "KorkunovLoopAnalysis"; 
      }