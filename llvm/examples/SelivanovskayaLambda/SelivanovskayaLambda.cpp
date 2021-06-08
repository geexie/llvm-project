#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Module.h"

llvm::Function *createLambdaFunction(llvm::Module *M, llvm::LLVMContext &C);
llvm::ExecutionEngine *createEngine(llvm::Module *M);
void JIT(llvm::ExecutionEngine *engine, llvm::Function *function, int arg);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    llvm::errs() << "Inform an argument to your expression.\n";
    return 1;
  } else {
    llvm::LLVMContext C;
    llvm::Module *M = new llvm::Module("lambda", C);
    llvm::Function *function = createLambdaFunction(M, C);
    M->dump();

    llvm::ExecutionEngine *engine = createEngine(M);
    JIT(engine, function, atoi(argv[1]));
  }
  return 0;
}

llvm::Function *createLambdaFunction(llvm::Module *M, llvm::LLVMContext &C) {
  llvm::IRBuilder<> builder(C);
  std::vector<llvm::Type *> Integers(1, llvm::Type::getInt32Ty(C));
  llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), Integers, false);
  llvm::Function *function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "lambda", M);
  llvm::BasicBlock *bb = llvm::BasicBlock::Create(C, "entry", function);
  builder.SetInsertPoint(bb);
  llvm::Argument *argX = function->arg_begin();
  argX->setName("x");
  VarExpr::varValue = argX;

  Lexer lexer;
  Parser parser(&lexer);
  Expr *expr = parser.parseExpr();
  llvm::Value *retVal = expr->gen(&builder, C, M);
  builder.CreateRet(retVal);

  return function;
}

llvm::ExecutionEngine *createEngine(llvm::Module *M) {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  std::string errStr;
  llvm::ExecutionEngine *engine =
      llvm::EngineBuilder(std::unique_ptr<llvm::Module>(M))
          .setErrorStr(&errStr)
          .setEngineKind(llvm::EngineKind::JIT)
          .create();

  if (!engine) {
    llvm::errs() << "Failed to construct ExecutionEngine: " << errStr << "\n";
  } else if (llvm::verifyModule(*M)) {
    llvm::errs() << "Error construcDng funcDon!\n";
  }

  return engine;
}

void JIT(llvm::ExecutionEngine *engine, llvm::Function *function, int arg) {
  std::vector<llvm::GenericValue> Args(1);
  Args[0].IntVal = llvm::APInt(32, arg);
  llvm::GenericValue retVal = engine->runFunction(function, Args);
  llvm::outs() << "Result: " << retVal.IntVal << "\n";
}