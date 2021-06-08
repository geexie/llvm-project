#include "llvm/Analysis/IlyinAnalysis.h"


namespace llvm {

	AnalysisKey IlyinAnalysis::Key;

	IlyinAnalysis::Result IlyinAnalysis::run(Function& F, FunctionAnalysisManager& FAM) {
		Result result;

		for (BasicBlock& BB : F) {
			result.basicBlocks++;
			for (Instruction& instr : BB) {
				if (auto BO = dyn_cast<BinaryOperator>(&instr)) {
					auto oc = BO->getOpcode();
					if (oc == Instruction::Add || oc == Instruction::FAdd) {
						result.adds++;
					}
					else if (oc == Instruction::Mul || oc == Instruction::FMul) {
						result.muls++;
					}
				}
				if (auto CI = dyn_cast<CallInst>(&instr)) {
					if (CI->getCalledFunction()->getName() == "powf") {
						result.pows++;
					}
				}
			}
		}

		return result;
	}


	void IlyinAnalysisInfo::print(raw_ostream& ostream) const {
		ostream << "Power operations: " << pows << "\n"
			<< "Add operations: " << adds << "\n"
			<< "Mul operations: " << muls << "\n"
			<< "Basic blocks: " << basicBlocks << "\n";
	}
}