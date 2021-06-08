#include "llvm/Transforms/ErmolaevLab2Pass/ErmolaevLab2Pass.h"
#define DEBUG_TYPE "ErmolaevLab2Pass"

using namespace llvm;

PreservedAnalyses ErmolaevLab2Pass::run(Function& func, FunctionAnalysisManager& AM) {
    auto pa = PreservedAnalyses::all();
    SmallVector<BinaryOperator*, 16> right_set;
    SmallVector<BinaryOperator*, 16> left_set;
    SmallVector<CallInst*, 16> pow_set;

    for (auto& I : instructions(func)) {
        if (auto bop = dyn_cast<BinaryOperator>(&I)) {
            if (auto FLconst = dyn_cast<ConstantFP>(bop->getOperand(0))) {
                if (((FLconst->getValue().convertToFloat() == 0.f) && (bop->getOpcode() == Instruction::FAdd)) ||
                    ((FLconst->getValue().convertToFloat() == 1.f) && (bop->getOpcode() == Instruction::FMul)))
                {
                    left_set.push_back(bop);
                    pa = PreservedAnalyses::none();
                }
            }

            else if (auto FLconst = dyn_cast<ConstantFP>(bop->getOperand(1))) {
                if (((FLconst->getValue().convertToFloat() == 0.f) && (bop->getOpcode() == Instruction::FAdd)) ||
                    ((FLconst->getValue().convertToFloat() == 1.f) && (bop->getOpcode() == Instruction::FMul)))
                {
                    right_set.push_back(bop);
                    pa = PreservedAnalyses::none();
                }
            }
        }
        else if (auto callinst = dyn_cast<CallInst>(&I)) {
            if (callinst->getCalledFunction()->getName() == StringRef("powf")) {
                if (auto FLconst = dyn_cast<ConstantFP>(callinst->getArgOperand(1))) {
                    if (FLconst->getValue().convertToFloat() == 2.f) {
                        pow_set.push_back(callinst);
                        pa = PreservedAnalyses::none();
                    }
                }
            }
        }
    }

    while (!right_set.empty()) {
        auto bop = right_set.pop_back_val();
        bop->replaceAllUsesWith(bop->getOperand(0));
        bop->eraseFromParent();
    }
    while (!left_set.empty()) {
        auto bop = left_set.pop_back_val();
        bop->replaceAllUsesWith(bop->getOperand(1));
        bop->eraseFromParent();
    }
    while (!pow_set.empty()) {
        auto callinst = pow_set.pop_back_val();
        auto mul = BinaryOperator::Create(Instruction::FMul, callinst->getOperand(0), callinst->getOperand(0));
        callinst->replaceAllUsesWith(mul);
        mul->insertBefore(callinst);
        callinst->eraseFromParent();
    }
    return pa;
}