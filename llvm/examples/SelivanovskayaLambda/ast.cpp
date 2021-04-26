#include "ast.hpp"



llvm::Value *VarExpr::varValue = NULL;

llvm::Value *NumExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const {
  return llvm::ConstantInt::get(llvm::Type::getInt32Ty(C), num);
}


llvm::Value *VarExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const {
  llvm::Value *var = VarExpr::varValue;
  return var ? var : NULL;
}


llvm::Value *AddExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const {
  llvm::Value *x = op1->gen(IRB, C, M);
  llvm::Value *y = op2->gen(IRB, C, M);
  return IRB->CreateAdd(x, y, "addtmp");
}


llvm::Value *MulExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const {
  llvm::Value *x= op1->gen(IRB, C, M);
  llvm::Value *y = op2->gen(IRB, C, M);
  return IRB->CreateMul(x, y, "multmp");
}


llvm::Value *PowExpr::gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *M) const {
  llvm::FunctionType *fTy = llvm::FunctionType::get( IRB->getDoubleTy(), {IRB->getDoubleTy(), IRB->getDoubleTy()}, false);
  auto myPow = M->getOrInsertFunction("pow", fTy);
  llvm::Value *x = op1->gen(IRB, C, M);
  llvm::Value *y = op2->gen(IRB, C, M);
  x = IRB->CreateSIToFP(x, llvm::Type::getDoubleTy(C));
  y = IRB->CreateSIToFP(y, llvm::Type::getDoubleTy(C));
  llvm::Value *ret = IRB->CreateCall(myPow, {x, y});
  ret = IRB->CreateFPToSI(ret, llvm::Type::getInt32Ty(C));

  return ret;
}
