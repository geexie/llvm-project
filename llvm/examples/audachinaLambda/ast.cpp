#include "ast.hpp"


llvm::Value* VariableExpr::VariableExpr = NULL;

llvm::Value* AddExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
  llvm::Value* fV = fOp->gen(builder, context, mod);
  llvm::Value* sV = sOp->gen(builder, context, mod);
  return builder->CreateAdd(fV, sV, "addtmp");
}
llvm::Value* PowerExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
  llvm::FunctionType *fTy = llvm::FunctionType::get(
    builder->getDoubleTy(), {builder->getDoubleTy(), builder->getDoubleTy()}, false);

  auto power = module->getOrInsertFunction("pow", fTy);

  llvm::Value* fV = fOp->gen(builder, context, mod);
  llvm::Value* sV = sOp->gen(builder, context, mod);

  fV = builder->CreateSIToFP(fV, llvm::Type::getDoubleTy(context));
  sV = builder->CreateSIToFP(sV, llvm::Type::getDoubleTy(context));

  llvm::Value* result = builder->CreateCall(power, {fV, sV});
  result = builder->CreateFPToSI(result, llvm::Type::getInt32Ty(context));

  return result;
}

llvm::Value* NumberExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
  return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), Val);
}

llvm::Value* VariableExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
  llvm::Value* var = VariableExpr::VariableExpr;
  return var ? var : NULL;
}



llvm::Value* MultoplExpr::gen(llvm::IRBuilder<> *builder, llvm::LLVMContext &context, llvm::Module *mod) const {
  llvm::Value* fV = fOp->gen(builder, context, mod);
  llvm::Value* sV = sOp->gen(builder, context, mod);
  return builder->CreateMul(fV, sV, "multmp");
}

