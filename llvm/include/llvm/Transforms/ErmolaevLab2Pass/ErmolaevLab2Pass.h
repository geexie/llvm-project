#include "llvm/ADT/Statistic.h"
#include "llvm/IR/PassManager.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

namespace llvm {

	class ErmolaevLab2Pass : public PassInfoMixin<ErmolaevLab2Pass> {
	public:
		PreservedAnalyses run(Function& F, FunctionAnalysisManager& AM);
		static bool isRequired() { return true; }
	};

}