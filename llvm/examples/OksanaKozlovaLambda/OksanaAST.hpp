#ifndef OKSANAAST_HPP
#define OKSANAAST_HPP

#include "llvm/IR/IRBuilder.h"

class OksanaExpr {
public:
    virtual ~OksanaExpr() {}
    virtual llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const = 0;
};

class NumExpr : public OksanaExpr {
public:
    NumExpr(int argNum) : num(argNum) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;
    static const unsigned int SIZE_INT = 32;

private:
  const int num;
};

class VarExpr : public OksanaExpr {
public:
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;
    static llvm::Value* varValue;
};

class AddExpr : public OksanaExpr {
public:
    AddExpr(OksanaExpr* op1Arg, OksanaExpr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
    llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;

private:
    const OksanaExpr* op1;
    const OksanaExpr* op2;
};

class MulExpr : public OksanaExpr {
public:
  MulExpr(OksanaExpr* op1Arg, OksanaExpr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;

private:
  const OksanaExpr* op1;
  const OksanaExpr* op2;
};

class PowExpr : public OksanaExpr {
public:
  PowExpr(OksanaExpr* op1Arg, OksanaExpr* op2Arg) : op1(op1Arg), op2(op2Arg) {}
  llvm::Value *gen(llvm::IRBuilder<> *builder, llvm::LLVMContext& con) const;

private:
  const OksanaExpr* op1;
  const OksanaExpr* op2;
};


#endif // OKSANAAST_HPP