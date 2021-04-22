add_llvm_component_library( LLVMErmolaevLab2Pass
  ErmolaevLab2Pass.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/ErmolaevLab2Pass
)