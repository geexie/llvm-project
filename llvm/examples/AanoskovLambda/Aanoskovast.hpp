#ifndef AANOSKOVAST_HPP
#define AANOSKOVAST_HPP

#include "llvm/IR/IRBuilder.h"

// Expr <- AddExpr
// Expr <- MulExpr
// Expr <- ConstExpr
// Expr <- VarExpr

class aanoskovExpr {
public:
  virtual ~aanoskovExpr() {}
  virtual llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const = 0;
};

class NumExpr : public aanoskovExpr {
public:
  NumExpr(int argNum) : num(argNum) {}
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;
  static const unsigned int SIZE_INT = 32;

private:
  const int num;
};

class VarExpr : public aanoskovExpr {
public:
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;
  static llvm::Value* varValue;
};

class AddExpr : public aanoskovExpr {
public:
  AddExpr(aanoskovExpr* op1Arg, aanoskovExpr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;

private:
  const aanoskovExpr* op1;
  const aanoskovExpr* op2;
};

class MulExpr : public aanoskovExpr {
public:
  MulExpr(aanoskovExpr* op1Arg, aanoskovExpr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;

private:
  const aanoskovExpr* op1;
  const aanoskovExpr* op2;
};

class PowExpr : public aanoskovExpr {
public:
  PowExpr(aanoskovExpr* op1Arg, aanoskovExpr* op2Arg) : op1(op1Arg), op2(op2Arg){}
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;

private:
  const aanoskovExpr* op1;
  const aanoskovExpr* op2;
};


#endif // AANOSKOVAST_HPP