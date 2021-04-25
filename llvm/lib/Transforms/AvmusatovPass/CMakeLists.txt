add_llvm_component_library(LLVMAvmusatovPass
  AvmusatovPass.cpp
  
  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/AvmusatovPass
)