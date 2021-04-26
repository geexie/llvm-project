#include "ast.hpp"


llvm::Value* VarExpr::varValue = NULL;

llvm::Value* NumExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *module) const {
  return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), num);
}

llvm::Value* VarExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *module) const {
  llvm::Value* var = VarExpr::varValue;
  return var ? var : NULL;
}

llvm::Value* AddExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *module) const {
  llvm::Value* v1 = op1->gen(builder, context, module);
  llvm::Value* v2 = op2->gen(builder, context, module);
  return builder->CreateAdd(v1, v2, "addtmp");
}

llvm::Value* MulExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *module) const {
  llvm::Value* v1 = op1->gen(builder, context, module);
  llvm::Value* v2 = op2->gen(builder, context, module);
  return builder->CreateMul(v1, v2, "multmp");
}

// example:
// ^ 4 + 5 2
// equals 16384
llvm::Value* PowExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *module) const {
  llvm::FunctionType *fTy = llvm::FunctionType::get(
    builder->getDoubleTy(), {builder->getDoubleTy(), builder->getDoubleTy()}, false);

  auto myPow = module->getOrInsertFunction("pow", fTy);

  llvm::Value* v1 = op1->gen(builder, context, module);
  llvm::Value* v2 = op2->gen(builder, context, module);
  
  v1 = builder->CreateSIToFP(v1, llvm::Type::getDoubleTy(context));
  v2 = builder->CreateSIToFP(v2, llvm::Type::getDoubleTy(context));

  llvm::Value* ret = builder->CreateCall(myPow, {v1, v2});
  ret = builder->CreateFPToSI(ret, llvm::Type::getInt32Ty(context));

  return ret;
}
