add_llvm_component_library( LLVMPankratovaTransformPass
  PankratovaTransformPass.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms

)
