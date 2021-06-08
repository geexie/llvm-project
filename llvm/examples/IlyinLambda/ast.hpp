#pragma once

#include "llvm/IR/IRBuilder.h"

class Expr {
public:
	virtual ~Expr() {}
	virtual llvm::Value* gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const = 0;
};

class NumExpr : public Expr {
private:
	const int num;

public:
	NumExpr(int argNum) : num(argNum) {}
	llvm::Value* gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const;
	static const unsigned int SIZE_INT = 32;
};

class VarExpr : public Expr {
public:
	llvm::Value* gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const;
	static llvm::Value* varValue;
};

class AddExpr : public Expr {
private:
	const Expr* op1;
	const Expr* op2;

public:
	AddExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
	llvm::Value* gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const;
};

class MulExpr : public Expr {
private:
	const Expr* op1;
	const Expr* op2;

public:
	MulExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
	llvm::Value* gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const;
};

class PowExpr : public Expr {
private:
	const Expr* op1;
	const Expr* op2;

public:
	PowExpr(Expr* op1Arg, Expr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
	llvm::Value* gen(llvm::IRBuilder<>* builder, llvm::LLVMContext& context, llvm::Module* module) const;
};
