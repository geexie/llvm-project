add_llvm_component_library( LLVMKMalyshevaLab3Pass
  KMalyshevaLab3Pass.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/KMalyshevaLab3Pass
) 