#include "llvm/Analysis/BogoroditskayaLoopAnalysis.h"

#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include <set>

using namespace llvm;

AnalysisKey BogoroditskayaLoopAnalysis::Key;

BogoroditskayaLoopAnalysis::Result BogoroditskayaLoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSA) {
    int64_t InvUpdatesCount = -1;

    if (PHINode* indVar = L.getCanonicalInductionVariable()) {
      // collect all binary operators which update this induction variable
      // in ideal vectorizable case it should be a single binary operator which updates loop induction
      SmallVector<BinaryOperator*, 16> updates;
      for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
        if (auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
          if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar) {
            updates.push_back(binOp);
          }
        }
      }
      InvUpdatesCount = updates.size();
      //errs() << *indVar << "is updated " << updates.size() << "times\n";
    }
    Result res = {InvUpdatesCount};
    return res;
}
