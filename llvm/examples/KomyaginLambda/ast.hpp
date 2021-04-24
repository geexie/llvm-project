#ifndef AST_HPP
#define AST_HPP

#include "llvm/IR/IRBuilder.h"

class Expr {
  public:
    virtual ~Expr() {}
    virtual llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const = 0;
};

class VarExpr : public Expr {
  public:
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const;
    static llvm::Value* varValue;
};

class NumExpr : public Expr {
  public:
    NumExpr(int argNum) : num(argNum) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const;
    static const unsigned int SIZE_INT = 32;

  private:
    const int num;
};

class MulExpr : public Expr {
  public:
    MulExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const;

  private:
    const Expr* op1;
    const Expr* op2;
};

class AddExpr : public Expr {
  public:
    AddExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const;

  private:
    const Expr* op1;
    const Expr* op2;
};

class PowExpr : public Expr {
  public:
    PowExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con, llvm::Module *mod) const;

  private:
    const Expr* op1;
    const Expr* op2;
};

#endif