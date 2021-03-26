#include "ast.hpp"

llvm::Value* VarExpr::varValue = NULL;

llvm::Value* NumExpr::gen(llvm::IRBuilder<> *builder, llvm::Module *mod, llvm::LLVMContext &context) const {
  return llvm::ConstantInt::get (llvm::Type::getInt32Ty(context), num);
}

llvm::Value* VarExpr::gen(llvm::IRBuilder<> *builder, llvm::Module *mod, llvm::LLVMContext &context) const {
  llvm::Value* var = VarExpr::varValue;
  return var ? var : NULL;
}

llvm::Value* AddExpr::gen(llvm::IRBuilder<> *builder, llvm::Module *mod, llvm::LLVMContext &context) const {
  llvm::Value* v1 = op1->gen(builder, mod, context);
  llvm::Value* v2 = op2->gen(builder, mod, context);
  return builder->CreateAdd(v1, v2, "addtmp");
}

llvm::Value* MulExpr::gen(llvm::IRBuilder<> *builder, llvm::Module *mod, llvm::LLVMContext &context) const {
  llvm::Value* v1 = op1->gen(builder, mod, context);
  llvm::Value* v2 = op2->gen(builder, mod, context);
  return builder->CreateMul(v1, v2, "multmp");
}

llvm::Value* PowExpr::gen(llvm::IRBuilder<> *builder, llvm::Module *mod, llvm::LLVMContext &context) const {
  llvm::Value* v1 = op1->gen(builder, mod, context);
  llvm::Value* v2 = op2->gen(builder, mod, context);

  auto c1 = builder->CreateCast(llvm::Instruction::CastOps::SIToFP, v1, llvm::Type::getFloatTy(context), "casttmp");
  auto c2 = builder->CreateCast(llvm::Instruction::CastOps::SIToFP, v2, llvm::Type::getFloatTy(context), "casttmp");

  std::vector<llvm::Type *> Floats(1, llvm::Type::getFloatTy(context));
  llvm::Function *fun = llvm::Intrinsic::getDeclaration(mod, llvm::Intrinsic::pow, Floats);

  llvm::Value *Ops[] = { c1, c2 };
  auto v3 = builder->CreateCall(fun, Ops, "powtmp");
  return builder->CreateCast(llvm::Instruction::CastOps::FPToSI, v3, llvm::Type::getInt32Ty(context), "casttmp");
}
