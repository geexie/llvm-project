#include "SazanovAST.h"
#include "SazanovLexer.h"
#include "SazanovParser.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetSelect.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"

llvm::Function *createLambdaFunction( llvm::Module *module, llvm::LLVMContext &context);
llvm::ExecutionEngine* createEngine(llvm::Module *module);
void JIT(llvm::ExecutionEngine* engine, llvm::Function* function, int arg);


int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		llvm::errs() << "Inform an argument to your expression.\n";
		return 1;
	}
	else
	{
		llvm::LLVMContext context;
		llvm::Module *module = new llvm::Module("lambda", context);
		llvm::Function *function = createLambdaFunction(module, context);
		module->dump();

		llvm::ExecutionEngine* engine = createEngine(module);
		JIT(engine, function, atoi(argv[1]));
	}
	return 0;
}

llvm::Function *createLambdaFunction( llvm::Module *module, llvm::LLVMContext &context)
{
	llvm::IRBuilder<> builder(context);
	std::vector<llvm::Type *> Integers(1, llvm::Type::getInt32Ty(context));
	llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), Integers, false);
	llvm::Function *function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "lambda", module);
	llvm::BasicBlock *bb = llvm::BasicBlock::Create(context, "entry", function);
	builder.SetInsertPoint(bb);
	llvm::Argument *argX = function->arg_begin();
	argX->setName("x");
	VarExpr::varValue = argX;

	Lexer lexer;
	Parser parser(&lexer);
	Expr* expr = parser.parseExpr();
	llvm::Value* retVal = expr->gen(&builder, context);
	builder.CreateRet(retVal);

	return function;
}

llvm::ExecutionEngine* createEngine(llvm::Module *module) {
	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmPrinter();

	std::string errStr;
	llvm::ExecutionEngine *engine = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module))
																	.setErrorStr(&errStr)
																	.setEngineKind(llvm::EngineKind::JIT)
																	.create();

	if (!engine)
	{
		llvm::errs() << "Failed to construct ExecutionEngine: " << errStr << "\n";
	}
	else if (llvm::verifyModule(*module))
	{
		llvm::errs() << "Error construcDng funcDon!\n";
	}

	return engine;
}

void JIT(llvm::ExecutionEngine* engine, llvm::Function* function, int arg)
{
	std::vector<llvm::GenericValue> Args(1);
	Args[0].IntVal = llvm::APInt(32, arg);
	llvm::GenericValue retVal = engine->runFunction(function, Args);
	llvm::outs() << "Result: " << retVal.IntVal << "\n";
}