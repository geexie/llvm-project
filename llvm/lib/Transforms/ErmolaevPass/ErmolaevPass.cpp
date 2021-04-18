#include "llvm/Transforms/ErmolaevPass/ErmolaevPass.h"
#define DEBUG_TYPE "ErmolaevPass"

using namespace llvm;

STATISTIC(FuncsAmount, "Number of function definitions");
STATISTIC(BasicBlocksAmount, "Number of basic blocks");
STATISTIC(AddsAmount, "Number of adds");
STATISTIC(MulsAmount, "Number of muls");
STATISTIC(LoopsAmount, "Number of loops");




void loopsCount(const Loop *loop) {
  LoopsAmount++;
  for (Loop::iterator loop_it = loop->begin(); loop_it != loop->end(); ++loop_it)
  {
    loopsCount(*loop_it);
  }
}


PreservedAnalyses ErmolaevPass::run(Function &func, FunctionAnalysisManager &AM) {
  if (!func.isDeclaration()) {
    FuncsAmount++;
    llvm::LoopAnalysis::Result &loops = AM.getResult<LoopAnalysis>(func);
    for (LoopInfo::iterator loop = loops.begin(); loop != loops.end(); ++loop) {
      loopsCount(*loop);
    }

    for (Function::iterator bb = func.begin(); bb != func.end(); ++bb) {
      BasicBlocksAmount++;
      for (BasicBlock::iterator instr = bb->begin(); instr != bb->end(); ++instr) {
        if (instr->getOpcode() == Instruction::Add || instr->getOpcode() == Instruction::FAdd){
            AddsAmount++;
        }
        if (instr->getOpcode() == Instruction::Mul || instr->getOpcode() == Instruction::FMul){
            MulsAmount++;
        }
      }
    }
  }
  return PreservedAnalyses::all();
}

#endif
