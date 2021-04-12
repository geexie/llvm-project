#pragma once

#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/udachinaLoopAnalysis.h"

using namespace llvm;

AnalysisKey udachinaLoopAnalysis::Key;

udachinaLoopAnalysis::Result udachinaLoopAnalysis::run(Loop& L, LoopAnalysisManager& LAM, LoopStandardAnalysisResults& LSAR) {
	
	Result data;

	if (PHINode* indVar = L.getCanonicalInductionVariable()) {
		SmallVector<BinaryOperator*, 16> val;
		
		for (unsigned int i = 0; i < indVar->getNumIncomingValues(); i++) {
			
			if (auto* bOper = dyn_cast<BinaryOperator>(indVar->getIncomingValue(i))) {
				
				if (bOper->getOperand(0) == indVar || bOper->getOperand(1) == indVar) {
					val.push_back(bOper);
				}
			}
		}
		data.val = val.size();
	}
	return data;
}