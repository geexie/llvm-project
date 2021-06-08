#ifndef MELNIKOVLAB4AST_H
#define MELNIKOVLAB4AST_H

#include "llvm/IR/IRBuilder.h"

// add, mul, const, pow inherit the Expr class
// gen() generates llvm IR

class Expr {
public:
    virtual ~Expr() {}
    virtual llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const = 0;
};


class NumExpr : public Expr { 
private:
    const int num;

public:
    NumExpr(int argNum) : num(argNum) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const override;
    static const unsigned int SIZE_INT = 32;
};


class VarExpr : public Expr {
public:
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const override;
    static llvm::Value* varValue;
};


class AddExpr : public Expr { 
private:
    const Expr* op1;
    const Expr* op2;

public:
    AddExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const override;
};


class MulExpr : public Expr { 
private:
    const Expr* op1;
    const Expr* op2;

public:
    MulExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const override;
};


class PowExpr : public Expr { 
private:
    const Expr* op1;
    const Expr* op2;

public:
    PowExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const override;
};


#endif // MELNIKOVLAB4AST_H