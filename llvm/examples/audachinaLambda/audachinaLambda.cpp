#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"

llvm::Function *createLambdaFunction( llvm::Module *mod, llvm::LLVMContext &context);
llvm::ExecutionEngine* createEngine(llvm::Module *mod);
void JIT(llvm::ExecutionEngine* engine, llvm::Function* function, int arg);

int main(int argc, char const *argv[])
{
  if (argc != 2) {
    llvm::errs() << "Put an argument :) \n";
    return 1;
  } else {
    llvm::LLVMContext context;
    llvm::Module *mod= new llvm::Module("lambda", context);
    llvm::Function *function = createLambdaFunction(mod, context);
    mod->dump();

    llvm::ExecutionEngine* engine = createEngine(mod);
    JIT(engine, function, atoi(argv[1]));
  }
  return 0;
}

llvm::Function *createLambdaFunction( llvm::Module *mod, llvm::LLVMContext &context) {
  llvm::IRBuilder<> builder(context);
  std::vector<llvm::Type *> Integers(1, llvm::Type::getInt32Ty(context));
  llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), Integers, false);
  llvm::Function *function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "lambda", mod);
  llvm::BasicBlock *bb = llvm::BasicBlock::Create(context, "entry", function);
  builder.SetInsertPoint(bb);
  llvm::Argument *argX = function->arg_begin();
  argX->setName("x");
  VarExpr::varValue = argX;

  Lexer lexer;
  Parser parser(&lexer);
  Expr* expr = parser.parseExpr();
  llvm::Value* retVal = expr->gen(&builder, context, mod);
  builder.CreateRet(retVal);

  return function;
}

llvm::ExecutionEngine* createEngine(llvm::Module *mod) {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  // LLVMInitializeNativeAsmPrinter();
  // LLVMInitializeNativeAsmParser();
  // LLVMLinkInMCJIT();

  std::string errStr;
  llvm::ExecutionEngine *engine = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(mod))
                                  .setErrorStr(&errStr)
                                  .setEngineKind(llvm::EngineKind::JIT)
                                .create();

  if (!engine) {
    llvm::errs() << "Failed :( : " << errStr << "\n";
  } else if (llvm::verifyModule(*mod)) {
    llvm::errs() << "Error :(\n";
  }

  return engine;
}

void JIT(llvm::ExecutionEngine* engine, llvm::Function* function, int arg) {
  std::vector<llvm::GenericValue> Args(1);
  Args[0].IntVal = llvm::APInt(32, arg);
  llvm::GenericValue retVal = engine->runFunction(function, Args);
  llvm::outs() << "Result: " << retVal.IntVal << "\n";
}