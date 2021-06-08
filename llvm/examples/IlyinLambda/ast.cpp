#include "ast.hpp"

llvm::Value* VarExpr::varValue = NULL;

llvm::Value* NumExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
	return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), num);
}

llvm::Value* VarExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
	llvm::Value* var = VarExpr::varValue;
	return var ? var : NULL;
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
	auto x = builder->CreateSIToFP(val1, llvm::Type::getDoubleTy(context));
	auto y = builder->CreateSIToFP(val2, llvm::Type::getDoubleTy(context));
	auto result = builder->CreateBinaryIntrinsic(llvm::Intrinsic::pow, x, y, nullptr, "powtmp");
	return builder->CreateFPToSI(result, llvm::Type::getInt32Ty(context));
}