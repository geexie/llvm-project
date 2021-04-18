add_llvm_component_library( LLVMBogoroditskaya3
  Bogoroditskaya3.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/Bogoroditskaya3

)