//===-- GeexieVec.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/GeexieVec/GeexieVec.h"

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"

#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/IntrinsicInst.h"

#include <set>

#define DEBUG_TYPE "geexie-vec"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

// create a vector of values
Value* vectorizeValue(Value* val, int VECTOR_SIZE, PHINode* indVar) {
  if (auto* constant = dyn_cast<ConstantData>(val)) {
    return ConstantDataVector::getSplat(VECTOR_SIZE, constant);
  } else if (auto* inst = dyn_cast<Instruction>(val)) {
    IRBuilder<> builder(inst);
    Value* initVec;
    if (auto* intType = dyn_cast<IntegerType>(inst->getType())) {
      initVec = ConstantDataVector::getSplat(VECTOR_SIZE, ConstantInt::get(intType, 0));
    } else {
      initVec = ConstantDataVector::getSplat(VECTOR_SIZE, ConstantFP::get(val->getType(), 0.0));
    }

    builder.SetInsertPoint(inst->getNextNode());

    Value* curVec = initVec;
    for (int i = 0; i < VECTOR_SIZE; i++) {
      curVec = builder.CreateInsertElement(curVec, inst, builder.getInt64(i));
    }

    // vector of inductive variables has to have its stride
    if (val == indVar) {
      std::vector<uint64_t> strides;
      for (uint64_t i = 0; i < (uint64_t)VECTOR_SIZE; i++) {
        strides.push_back(i);
      }

      ArrayRef<uint64_t> strideRef(strides);
      Value* strideVec = ConstantDataVector::get(indVar->getContext(), strideRef);
      Value* resultVec = builder.CreateAdd(curVec, strideVec);
      return resultVec;

    } else {
      return curVec;
    }
  }

  return NULL;
}

PreservedAnalyses handleLoopVec(Loop *L) {
  int VECTOR_SIZE = 4;
  errs() << "name: " << L->getName() << "\n";

  auto indVar = L->getCanonicalInductionVariable();
  auto getExitingConditional = [](Loop *L) -> ICmpInst* {
    if (BasicBlock* latchBlock = L->getExitingBlock()) {
      Instruction& lbInst = *latchBlock->rbegin();
      if (auto* exitingBranch = dyn_cast<BranchInst>(&lbInst)) {
        // branch must have a condition (which sets the loop bound)
        if (exitingBranch->isConditional()) {
          return dyn_cast<ICmpInst>(exitingBranch->getCondition());
        }
      }
    }
    return nullptr;
  };
  // find indvar update instruction
  auto getIVUpdate = [](PHINode* indVar) -> BinaryOperator* {
    SmallVector<BinaryOperator*, 16> updates;
    for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
      if (auto* binOp = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
        if (binOp->getOperand(0) == indVar || binOp->getOperand(1) == indVar) {
          updates.push_back(binOp);
        }
      }
    }
    return (updates.size() == 1) ? updates.pop_back_val() : nullptr;
  };
  auto getLoopBound = [](PHINode* indVar, ICmpInst* cmp) -> Value* {
    if (cmp != nullptr && indVar != nullptr) {
      Value* op1 = cmp->getOperand(0);
      Value* op2 = cmp->getOperand(1);
      return (op1 == indVar) ? op2 : (op2 == indVar ? op1 : nullptr);
    }
    return nullptr;
  };

  ICmpInst* cmp = getExitingConditional(L);
  Value* loopBound = getLoopBound(indVar, cmp);
  BinaryOperator* indVarUpdate = getIVUpdate(indVar);

  if (indVarUpdate == nullptr) {
    errs() << "update for induction variable is not found\n";
    return PreservedAnalyses::all();
  }

  if (loopBound == nullptr) {
    errs() << "loop bound cannot be determined\n";
    return PreservedAnalyses::all();
  }

  if (cmp == nullptr) {
    errs() << "cmp for induction variable is not found\n";
    return PreservedAnalyses::all();
  }

  // check loop bound and see if it is divisible by VECTOR_SIZE
  // loop bound must be a constant. otherwise we can't vectorize
  bool hasVectorizableLoopBound = false;
  if (auto* loopBoundConst = dyn_cast<ConstantInt>(loopBound)) {
    hasVectorizableLoopBound = loopBoundConst->getSExtValue() % VECTOR_SIZE == 0;
  }

  if (!hasVectorizableLoopBound) {
    errs() << "loop bound is not vectorizable\n";
    return PreservedAnalyses::all();
  }

  // check that all instructions in the body are vectorizable
  std::set<Value*> vectorizedSet;
  for (auto &B : L->getBlocks()) {
    for (auto &I : *B) {
      errs() << I << "\n";
      if (&I == cmp || &I == indVar || &I == indVarUpdate) {

      // approximate checking for cross-iteration dependencies by
      // checking if GEPs index through the inductive variable only
      } else if (auto* gep = dyn_cast<GetElementPtrInst>(&I)) {
        for (auto& index : gep->indices()) {
          if (index != indVar && !L->isLoopInvariant(index)) {
            errs() << "cross gep! index: " << *index << "\n";
            return PreservedAnalyses::all();
          }
        }
        vectorizedSet.insert(gep);
      } else if (auto* branch = dyn_cast<BranchInst>(&I)) {
        if (branch->isConditional()) {
          if (L->isLoopInvariant(branch->getCondition())) {
            errs() << "cross gep!" << "\n";
            return PreservedAnalyses::all();
          }
        }
      } else {
        for (unsigned int i = 0; i < I.getNumOperands(); i ++) {
          Value* operand = I.getOperand(i);
          if (vectorizedSet.count(operand) == 0 && !L->isLoopInvariant(operand) && operand != indVar) {
            errs() << "cross gep #2!" << "\n";
            return PreservedAnalyses::all();
          }
        }
        vectorizedSet.insert(&I);
      }
    }
  }

  errs() << "VECTORIZE!!!!!\n";

  if (true) {
    // maintain a map of vectorized instructions
    // if an instruction reads a vectorized instruction,
    // it is also vectorized
    std::map<Value*,Value*> valmap;
    std::list<Instruction*> removedInstrs;
    for (auto &B : L->getBlocks()) {
      for (auto& I : *B) {
        if (&I == cmp || &I == indVarUpdate || &I == indVar) {

        // GEP: array accesses should be vectorized by bitcasting results
        // of GEPs from t* to <n x t>*, where n is the vector size
        } else if (auto* gep = dyn_cast<GetElementPtrInst>(&I)) {
          bool isGEPLoopInvariant = true;
          for (auto& index : gep->indices()) {
            isGEPLoopInvariant = isGEPLoopInvariant && L->isLoopInvariant(index);
          }

          if (!isGEPLoopInvariant) {
            IRBuilder<> builder(gep);
            builder.SetInsertPoint(gep->getNextNode());
            if (auto* elementPtrType = dyn_cast<PointerType>(gep->getType())) {
              Type* arrIndType =
                  PointerType::getUnqual(
                      VectorType::get(elementPtrType->getElementType(),
                          unsigned(VECTOR_SIZE), false)); // FIXME: use something like 128/32
              Value* arrayIndVec = builder.CreateBitCast(gep, arrIndType);
              valmap.insert(std::pair<Value*,Value*>(gep,arrayIndVec));
            }
          }

        // generic branch that checks operands of instructions
        } else if (dyn_cast<BinaryOperator>(&I) != NULL
                || dyn_cast<ICmpInst>(&I) != NULL
                || dyn_cast<LoadInst>(&I) != NULL
                || dyn_cast<StoreInst>(&I) != NULL) {

          for (unsigned int i = 0; i < I.getNumOperands(); i++) {
            Value* operand = I.getOperand(i);
            std::map<Value*,Value*>::iterator it = valmap.find(operand);

            if (it != valmap.end()) {
              I.setOperand(i, it->second);

            } else {
              Value* newOperand = vectorizeValue(operand, VECTOR_SIZE, indVar);
              I.setOperand(i, newOperand);
              valmap.insert(std::pair<Value*,Value*>(operand, newOperand));
            }
          }

          Type* retType = I.getType();
          if (retType != NULL && dyn_cast<StoreInst>(&I) == NULL) {
            Type* retVecType = VectorType::get(retType, unsigned(VECTOR_SIZE), false);
            I.mutateType(retVecType);
          }
          valmap.insert(std::pair<Value*,Value*>(&I, &I));
        }
      }
    }

    // remove instructions out of the loop (so iterators aren't messed up)
    for (auto* removedInstr : removedInstrs) {
      removedInstr->eraseFromParent();
    }

    // finally, update inductive variable stride to be VECTOR_SIZE
    if (indVarUpdate->getOperand(0) == indVar) {
      indVarUpdate->setOperand(1, ConstantInt::get(indVar->getType(), VECTOR_SIZE));
    } else {
      indVarUpdate->setOperand(0, ConstantInt::get(indVar->getType(), VECTOR_SIZE));
    }
  }

  return PreservedAnalyses::none();;
}

static void collectIntermostLoops(Loop &L, SmallVectorImpl<Loop *> &V) {
  if (L.isInnermost()) {
    if (!!L.getCanonicalInductionVariable()) {
      V.push_back(&L);
    }
    return;
  }

  for (Loop *InnerL : L)
    collectIntermostLoops(*InnerL, V);
}

// Naive loop vectorize. Asumes:
// 1. Loops are not explicitly vectorized
// 1. Supports only constant trip count
PreservedAnalyses GeexieVecPass::run(Function &F, FunctionAnalysisManager &AM) {
  auto pa = PreservedAnalyses::all();

  SmallVector<Loop*, 16> work_set;
  for (auto& L : AM.getResult<LoopAnalysis>(F)) {
    collectIntermostLoops(*L, work_set);
  }

  errs() << "running vec pass " << work_set.size() << " \n";

  while (!work_set.empty()) {
    auto L = work_set.pop_back_val();
    pa.intersect(handleLoopVec(L));
  }

  return pa;
}
