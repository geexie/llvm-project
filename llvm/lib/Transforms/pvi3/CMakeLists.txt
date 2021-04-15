add_llvm_component_library( LLVMBaturinaPass3
  BaturinaPass3.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/BaturinaPass3
) 