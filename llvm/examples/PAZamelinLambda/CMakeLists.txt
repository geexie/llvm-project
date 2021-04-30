set(LLVM_LINK_COMPONENTS
  Core
  ExecutionEngine
  Interpreter
  MC
  MCJIT
  Support
  nativecodegen
)

set(HEADER_LIST
  parser.hpp
  lexer.hpp
  ast.hpp
)

set(SRC_LIST
  lambda.cpp
  parser.cpp
  lexer.cpp
  ast.cpp
)

add_llvm_example(PAZamelinLambda ${HEADER_LIST} ${SRC_LIST})