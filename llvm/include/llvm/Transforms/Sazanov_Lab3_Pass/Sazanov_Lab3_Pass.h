#ifndef LLVM_TRANFORMS_SAZANOV_LAB3_PASS_H
#define LLVM_TRANFORMS_SAZANOV_LAB3_PASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/ADT/Statistic.h"

namespace llvm
{
	
class Sazanov_Lab3_Pass : public PassInfoMixin<Sazanov_Lab3_Pass>
{
public:
	PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
	static bool isRequired() { return true; }
};
	
} //namespace llvm

#endif //LLVM_TRANFORMS_SAZANOV_LAB3_PASS_H