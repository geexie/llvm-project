#include "llvm/Transforms/ArtyomLavrov/ArtyomLavrovlab1.h"
#include "llvm/IR/InstIterator.h" 
#include "llvm/Analysis/LoopInfo.h" 
#include "llvm/ADT/Statistic.h"
#include <set>

#define DEBUG_TYPE "ArtyomLavrovlab1"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(FuncCounter, "Function counter");
ALWAYS_ENABLED_STATISTIC(BlockCounter, "Block counter");
ALWAYS_ENABLED_STATISTIC(OpCounter, "Arithmetic operation counter");
ALWAYS_ENABLED_STATISTIC(LoopCounter, "Loop counter");

PreservedAnalyses DenisKabanovLab1Pass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << "function: " << F.getName() << "\n";
  FuncCounter++;
  for (auto BB = F.begin(); BB != F.end(); ++BB){
    errs() << "    base block: " << BB->getName() << "\n";
    BlockCounter++;
    for (auto I = BB->begin(); I != BB->end(); ++I){
      errs() << "        instruction: " << I->getOpcode() << "\n";
      // id - instruction
      // 1 - return
      // 13 - "+" 
      // 15 - "-" 
      // 17 - "*" 
      // 20 - "/" 
      // 23 - "%" 
      std::set<int> Operations{13, 15, 17, 20, 23};
      if (Operations.find(I->getOpcode()) != Operations.end())
        OpCounter++;
    }
  }

  //}
  auto& LA = AM.getResult<LoopAnalysis>(F); 
  for (auto& L : LA){
    errs() << "        loop:" << L->getName() << "\n";
    LoopCounter++;
  }
  errs() << "Total stats after function: " << F.getName()
         << "\n\tFunction counter: " << FuncCounter
         << "\n\tBlock counter: " << BlockCounter
         << "\n\tArithmetic operation counter: " << OpCounter
         << "\n\tLoop counter: " << LoopCounter << "\n";
  return PreservedAnalyses::all();
}