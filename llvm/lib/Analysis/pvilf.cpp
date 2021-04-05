#include "llvm/Analysis/pvilf.h"
#include <set>

using namespace llvm;

AnalysisKey pvilf::Key;

pvilf::Result
pvilf::run(Loop &L, LoopAnalysisManager &LAM,
                         LoopStandardAnalysisResults &LSAR) {
  int64_t updcounter = 0;

  if (PHINode *indVar = L.getCanonicalInductionVariable()) {
    SmallVector<BinaryOperator *, 16> updates;
    for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
      if (auto *binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
        if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar) {
          updates.push_back(binOp);
        }
      }
    }
    updcounter = updates.size();
  }
  Result res = {updcounter};
  return res;
}