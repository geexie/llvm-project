#include "ast.hpp"


llvm::Value* VarExpr::varValue = NULL;

llvm::Value* NumExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context,  llvm::Module *mod) const {
  return llvm::ConstantInt::get (llvm::Type::getInt32Ty(context), num);
}

llvm::Value* VarExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
  llvm::Value* var = VarExpr::varValue;
  return var ? var : NULL;
}

llvm::Value* MulExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
  llvm::Value* v1 = op1->gen(builder, context, mod);
  llvm::Value* v2 = op2->gen(builder, context, mod);
  return builder->CreateMul(v1, v2, "multmp");
}

llvm::Value* AddExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
  llvm::Value* v1 = op1->gen(builder, context, mod);
  llvm::Value* v2 = op2->gen(builder, context, mod);
  return builder->CreateAdd(v1, v2, "addtmp");
}

llvm::Value* PowExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
    llvm::Value* v1 = op1->gen(builder, context, mod);
    llvm::Value* v2 = op2->gen(builder, context, mod);

    v1 = builder->CreateSIToFP(v1, llvm::Type::getDoubleTy(context));
    v2 = builder->CreateSIToFP(v2, llvm::Type::getDoubleTy(context));

    auto Pow = mod->getOrInsertFunction("pow",  llvm::FunctionType::get(
        builder->getDoubleTy(), {builder->getDoubleTy(), builder->getDoubleTy()}, false));

    llvm::Value* ret = builder->CreateCall(Pow, {v1, v2});
    ret = builder->CreateFPToSI(ret, llvm::Type::getInt32Ty(context));

    return ret;
}
