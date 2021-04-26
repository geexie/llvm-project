#include "llvm/Transforms/Strakhov2/Strakhov2.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"


using namespace llvm;

PreservedAnalyses Strakhov2::run(Function &F, FunctionAnalysisManager &AM) {

	auto pa = PreservedAnalyses::all();

	SmallVector<BinaryOperator*, 16> wset0;
	SmallVector<BinaryOperator*, 16> wset1;
	SmallVector<CallBase*, 16> pows;

	
	for (auto& I : instructions(F)) {
		
		
		if (auto BinOper = dyn_cast<BinaryOperator>(&I)) {
			
			auto RHSC_0 = dyn_cast<ConstantFP>(BinOper->getOperand(0));
			auto RHSC_1 = dyn_cast<ConstantFP>(BinOper->getOperand(1));
			
			if (RHSC_0 || RHSC_1) {

				if (RHSC_1) {
					
					if (RHSC_1->getValue().convertToFloat() == 1.f && BinOper->getOpcode() == Instruction::FMul) {
						wset1.push_back(BinOper);
						pa = PreservedAnalyses::none();
					}
					
					else if (RHSC_1 && RHSC_1->getValue().convertToFloat() == 0.f && BinOper->getOpcode() == Instruction::FAdd) {
						wset1.push_back(BinOper);
						pa = PreservedAnalyses::none();
					}
				}
				
				else if (RHSC_0) {
					
					if (RHSC_0->getValue().convertToFloat() == 1.f && BinOper->getOpcode() == Instruction::FMul) {
						wset0.push_back(BinOper);
						pa = PreservedAnalyses::none();
					}
					
					else if (RHSC_0 && RHSC_0->getValue().convertToFloat() == 0.f && BinOper->getOpcode() == Instruction::FAdd) {
						wset0.push_back(BinOper);
						pa = PreservedAnalyses::none();
					}
				}
				
				
				
			}
		}

		if (auto pow = dyn_cast<CallBase>(&I)) {
			if (pow->getCalledFunction()->getName() == "powf") {
				if (auto RHSC = dyn_cast<ConstantFP>(pow->getArgOperand(1))) { 
					if (RHSC->getValue().convertToFloat() == 2.f) {
						pows.push_back(pow);
						pa = PreservedAnalyses::none();
					}
				}
			}
		}
	}

	while (!wset1.empty()) {
		auto BinOper = wset1.pop_back_val();
		BinOper->replaceAllUsesWith(BinOper->getOperand(0));
		BinOper->eraseFromParent();
	}


	while (!wset0.empty()) {
		auto BinOper = wset0.pop_back_val();
		BinOper->replaceAllUsesWith(BinOper->getOperand(1));
		BinOper->eraseFromParent();
	} 


	while (!pows.empty()) {
		auto Cin = pows.pop_back_val();
		auto operand = Cin->getArgOperand(0);
		auto BinOper = BinaryOperator::Create(Instruction::FMul, operand, operand);
		Cin->replaceAllUsesWith(BinOper);
		BinOper->insertAfter(Cin);
		Cin->eraseFromParent();
	}

	return pa;
}