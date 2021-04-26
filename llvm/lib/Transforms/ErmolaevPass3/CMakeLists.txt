add_llvm_component_library( LLVMErmolaevPass3
  ErmolaevPass3.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/ErmolaevPass3
) 