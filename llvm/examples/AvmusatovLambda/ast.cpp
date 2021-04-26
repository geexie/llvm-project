#include "ast.hpp"

llvm::Value* VarExpr::varValue = NULL;

llvm::Value* NumExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), num);
}

llvm::Value* VarExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
    llvm::Value* vv = VarExpr::varValue;
    return vv ? vv : NULL;
}

llvm::Value* AddExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
    llvm::Value* x = op1->gen(builder, context, module);
    llvm::Value* y = op2->gen(builder, context, module);
    return builder->CreateAdd(x, y, "addtmp");
}

llvm::Value* MulExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
    llvm::Value* x = op1->gen(builder, context, module);
    llvm::Value* y = op2->gen(builder, context, module);
    return builder->CreateMul(x, y, "multmp");
}

llvm::Value* PowExpr::gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const {
    llvm::Value* x = op1->gen(builder, context, module);
    llvm::Value* y = op2->gen(builder, context, module);

    x = builder->CreateSIToFP(x, llvm::Type::getDoubleTy(context));
    y = builder->CreateSIToFP(y, llvm::Type::getDoubleTy(context));

    llvm::Value* result = builder->CreateBinaryIntrinsic(llvm::Intrinsic::pow, x, y, nullptr, "powtmp");
    return builder->CreateFPToSI(result, llvm::Type::getInt32Ty(context));
}
