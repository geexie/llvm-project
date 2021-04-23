#include "llvm/Transforms/akUdachinaPass/akUdachinaPass.h"
#define DEBUG_TYPE "akUdachinaPass"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"


using namespace llvm;

STATISTIC(totalDef, "Number of Function definitions");
STATISTIC(totalLoops, "Number of Loops");
STATISTIC(totalBlocks, "Number of Basic blocks");
STATISTIC(totalAdd, "Number of Add instructions");
STATISTIC(totalMul, "Number of Mul instructions");

void countLoops(const Loop *L) {
  totalLoops++;
  auto loops = L->getSubLoops();
  for (auto L = loops.begin(); L != loops.end(); L++) {
    countLoops(*L);
  }
}

PreservedAnalyses akUdachinaPass::run(Function &Func,
                                      FunctionAnalysisManager &AM) {
  if (!Func.isDeclaration()) {
    totalDef++;
  }
  llvm::LoopAnalysis::Result &loops = AM.getResult<LoopAnalysis>(Func);
  for (auto L = loops.begin(); L != loops.end(); L++) {
    countLoops(*L);
  }
  for (BasicBlock &BB : Func) {
    totalBlocks++;
    for (Instruction &I : BB) {
      std::string instructionName = std::string(I.getOpcodeName());
      if (instructionName == "add" || instructionName == "fadd") {
        totalAdd++;
      } else if (instructionName == "mul" || instructionName == "fmul") {
        totalMul++;
      }
    }
  }
  return PreservedAnalyses::all();
}