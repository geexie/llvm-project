#include "ast.hpp"


llvm::Value* VarExpr::varValue = NULL;

llvm::Value* NumExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *m) const {
    return llvm::ConstantInt::get (llvm::Type::getInt32Ty(context), num);
}

llvm::Value* VarExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *m) const {
    llvm::Value* var = VarExpr::varValue;
    return var ? var : NULL;
}

llvm::Value* AddExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *m) const {
    llvm::Value* v1 = op1->gen(builder, context, m); llvm::Value* v2 = op2->gen(builder, context, m);
    return builder->CreateAdd(v1, v2, "addtmp");
}

llvm::Value* MulExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *m) const {
    llvm::Value* v1 = op1->gen(builder, context, m); llvm::Value* v2 = op2->gen(builder, context, m);
    return builder->CreateMul(v1, v2, "multmp");
}

llvm::Value* powFunc::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *m) const {
    llvm::Value* v1 = op1->gen(builder, context, m); llvm::Value* v2 = op2->gen(builder, context, m);
    auto pow = llvm::Intrinsic::getDeclaration(m, llvm::Intrinsic::pow, {llvm::Type::getFloatTy(context)});
    llvm::Value* ret = builder->CreateCall(pow, //{v1, v2},
                                    {builder->CreateSIToFP(v1,llvm::Type::getFloatTy(context)),
                                     builder->CreateSIToFP(v2,llvm::Type::getFloatTy(context))},
                                     "powtmp");
    //return ret;
    return builder->CreateFPToSI(ret, llvm::Type::getInt32Ty(context));
}