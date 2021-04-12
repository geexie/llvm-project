add_llvm_component_library( LLVMakUdachinaPass
  akUdachinaPass.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms

)