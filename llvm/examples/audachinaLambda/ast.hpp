#ifndef AST_HPP
#define AST_HPP

#include "llvm/IR/IRBuilder.h"
// Expr - Base class for all expression nodes.
class Expr {
public:
  virtual ~Expr() {}
  virtual llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const = 0;
};

// NumberExpr - Expression class for numeric literals
class NumberExpr : public Expr {
private:
  const int  Val;

public:
  NumberExpr(int Val) : Val(Val) {}
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const;
  static const unsigned int SIZE_INT = 32;
};

// VariableExpr - Expression class for referencing a variable
class VariableExpr : public Expr {
  std::string Name;

public:
  static llvm::Value* varValue;
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const;
};

#AddExpr Expression class for sum
class AddExpr: public Expr{
public:
  AddExpr(Expr* fArg, Expr* sArg) : fOp(fArg), sOp(sArg) {}
  llvm::Value *gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *mod) const;

private:
  const Expr* fOp;
  const Expr* sOp;
}
// MultoplExpr Expression class for multiplication
class MultoplExpr: public Expr{
public:
  MultoplExpr(Expr* fArg, Expr* sArg) : fOp(fArg), sOp(sArg) {}
  llvm::Value *gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *mod) const;

private:
  const Expr* fOp;
  const Expr* sOp;
}

class PowerExpr:public Expr{
  PowerExpr(Expr* fArg, Expr* sArg) : fOp(fArg), sOp(sArg) {}
  llvm::Value *gen(llvm::IRBuilder<> *IRB, llvm::LLVMContext &C, llvm::Module *mod) const;

private:
  const Expr* fOp;
  const Expr* sOp;
}

#endif