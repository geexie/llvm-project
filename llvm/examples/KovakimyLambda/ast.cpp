#include "ast.hpp"


llvm::Value* VarExpr::varValue = NULL;

llvm::Value* NumExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const
{
  return llvm::ConstantInt::get(llvm::Type::getInt32Ty(C), num);
}

llvm::Value* VarExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const
{
  llvm::Value* var = VarExpr::varValue;
  return var ? var : NULL;
}

llvm::Value* AddExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const
{
  llvm::Value* v1 = op1->gen(IRB, C, M);
  llvm::Value* v2 = op2->gen(IRB, C, M);
  return IRB->CreateAdd(v1, v2, "addtmp");
}

llvm::Value* MulExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const
{
  llvm::Value* v1 = op1->gen(IRB, C, M);
  llvm::Value* v2 = op2->gen(IRB, C, M);
  return IRB->CreateMul(v1, v2, "multmp");
}

llvm::Value* PowExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const
{
  llvm::FunctionType *fTy = llvm::FunctionType::get(IRB->getDoubleTy(), {IRB->getDoubleTy(), IRB->getDoubleTy()}, false);
  auto myPow = M->getOrInsertFunction("pow", fTy);
  llvm::Value* v1 = op1->gen(IRB, C, M);
  llvm::Value* v2 = op2->gen(IRB, C, M);
  v1 = IRB->CreateSIToFP(v1, llvm::Type::getDoubleTy(C));
  v2 = IRB->CreateSIToFP(v2, llvm::Type::getDoubleTy(C));
  llvm::Value* ret = IRB->CreateCall(myPow, {v1, v2});
  ret = IRB->CreateFPToSI(ret, llvm::Type::getInt32Ty(C));
  
  return ret;
}