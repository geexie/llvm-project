#include "ast.hpp"

llvm::Value* VarExpr::varValue = nullptr;

llvm::Value* NumExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
	return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), num);
}

llvm::Value* VarExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
	llvm::Value* var = VarExpr::varValue;
	return var ? var : nullptr;
}

llvm::Value* AddExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
	llvm::Value* val1 = op1->gen(builder, context, module);
	llvm::Value* val2 = op2->gen(builder, context, module);
	return builder->CreateAdd(val1, val2, "addtmp");
}

llvm::Value* MulExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
	llvm::Value* val1 = op1->gen(builder, context, module);
	llvm::Value* val2 = op2->gen(builder, context, module);
	return builder->CreateMul(val1, val2, "multmp");
}

llvm::Value* PowExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
	llvm::Value* val1 = op1->gen(builder, context, module);
	llvm::Value* val2 = op2->gen(builder, context, module);
	
	// cast first argument to double
	llvm::Value* base = builder->CreateSIToFP(val1, llvm::Type::getDoubleTy(context));

	// See https://llvm.org/docs/LangRef.html#llvm-powi-intrinsic
	// declare double    @llvm.powi.f64(double %Val, i32 %power)
	llvm::CallInst* resultFP = builder->CreateBinaryIntrinsic(llvm::Intrinsic::powi, base, val2, nullptr, "powtmp");
	
	// cast resultFP back to i32
	llvm::Value* result = builder->CreateFPToSI(resultFP, llvm::Type::getInt32Ty(context));

	return result;
} 