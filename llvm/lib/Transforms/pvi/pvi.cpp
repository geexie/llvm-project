#include "llvm/Transforms/pvi/pvi.h"

using namespace llvm;

#define DEBUG_TYPE "pvi"

/*
STATISTIC(FuncsCounter, "Number of functions");
STATISTIC(LoopsCounter, "Number of loops");
STATISTIC(BasicBlockCounter, "Number of basic blocks");
STATISTIC(AddCounter, "Number of +");
STATISTIC(MulCounter, "Number of *");

void countLoops(Loop* loop) {
    LoopsCounter++;
    for (Loop::iterator it = loop->begin(); it != loop->end(); ++it){
        countLoops(*it);
	}
}


PreservedAnalyses pvi::run(Function &F, FunctionAnalysisManager &AM) {
	if (!F.isDeclaration()) {
		FuncsCounter++;
	  
		llvm::LoopAnalysis::Result& loops = AM.getResult<LoopAnalysis>(F);
		for (Loop::iterator loop_it = loops.begin(); loop_it != loops.end(); ++loop_it){
			countLoops(*loop_it);
		}
	
	
		for (Function::iterator bb_it = F.begin(); bb_it != F.end(); ++bb_it) {
			BasicBlockCounter++;
			
			for (BasicBlock::iterator instr_it = bb_it->begin(); instr_it != bb_it->end(); ++instr_it)
			{
				if (std::string(instr_it->getOpcodeName()) == "add" || std::string(instr_it->getOpcodeName()) == "fadd") 
					AddCounter++;
				if (std::string(instr_it->getOpcodeName()) == "mul" || std::string(instr_it->getOpcodeName()) == "fmul")
					MulCounter++;
			}
		}
	}
	
	return PreservedAnalyses::all();
} 
*/

PreservedAnalyses pvi::run(Function &F, FunctionAnalysisManager &AM) {
    auto pa = PreservedAnalyses::all();
    SmallVector<BinaryOperator*, 16> r_wark_set;
    SmallVector<BinaryOperator*, 16> l_wark_set;
    SmallVector<CallInst*, 16> p_wark_set;
    
    for (auto& I : instructions(F)) {
		
		if (auto CI = dyn_cast<CallInst>(&I)){
          if(CI->getCalledFunction()->getName() == "powf") {
            if(auto item = dyn_cast<ConstantFP>(CI->getArgOperand(1))){
              if (item->getValue().convertToFloat() == 2.f){
                p_wark_set.push_back(CI);
                pa = PreservedAnalyses::none();
              }
            }
          }
        }
		
        if (auto BO = dyn_cast<BinaryOperator>(&I)){
			auto LHSC = dyn_cast<ConstantFP>(BO->getOperand(0));
			auto RHSC = dyn_cast<ConstantFP>(BO->getOperand(1));
			
			if(BO->getOpcode() == Instruction::FAdd){
                if(LHSC || RHSC){
                    if(RHSC && RHSC->getValue().convertToFloat() == 0.f) {
                        r_wark_set.push_back(BO);
                        pa = PreservedAnalyses::none();
                    }
                    else if(LHSC && LHSC->getValue().convertToFloat() == 0.f) {
                        l_wark_set.push_back(BO);
                        pa = PreservedAnalyses::none();
                    }
                }
            }
			else if (BO->getOpcode() == Instruction::FMul){
                if(LHSC || RHSC){
                    if(RHSC && RHSC->getValue().convertToFloat() == 1.f) {
                        r_wark_set.push_back(BO);
                        pa = PreservedAnalyses::none();
                    }
                    else if(LHSC && LHSC->getValue().convertToFloat() == 1.f) {
                        l_wark_set.push_back(BO);
                        pa = PreservedAnalyses::none();
                    }
                }
            }
        }
    }

    while (!r_wark_set.empty()) {
        auto BO = r_wark_set.pop_back_val();
        BO->replaceAllUsesWith(BO->getOperand(0));
        BO->eraseFromParent();
    }
	
    while (!l_wark_set.empty()) {
        auto BO = l_wark_set.pop_back_val();
        BO->replaceAllUsesWith(BO->getOperand(1));
        BO->eraseFromParent();
    }
	
    while (!p_wark_set.empty()) {
        auto pwsi = p_wark_set.pop_back_val();
        auto mul = BinaryOperator::Create(Instruction::FMul, pwsi->getOperand(0), pwsi->getOperand(0));
        pwsi->replaceAllUsesWith(mul);
        mul->insertBefore(pwsi);
        pwsi->eraseFromParent();
    }
 
    return pa;
}