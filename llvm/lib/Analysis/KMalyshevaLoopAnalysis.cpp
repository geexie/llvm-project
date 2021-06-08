#include "llvm/Analysis/KMalyshevaLoopAnalysis.h"

using namespace llvm;

AnalysisKey KMalyshevaLoopAnalysis::Key;

KMalyshevaLoopAnalysis::Result
KMalyshevaLoopAnalysis::run(Loop &L, LoopAnalysisManager &LAM,
                          LoopStandardAnalysisResults &LSAR) {
  Result result;

  if (PHINode *indVar = L.getCanonicalInductionVariable()) {
    SmallVector<BinaryOperator *, 16> updates;
    for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
      if (auto *binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
        if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar) {
          updates.push_back(binOp);
        }
      }
    }
    result.upd_count = updates.size();
  }
  return result;
}