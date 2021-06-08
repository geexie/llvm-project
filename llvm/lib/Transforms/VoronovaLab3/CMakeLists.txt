add_llvm_component_library( LLVMVoronovaLab3
  VoronovaLab3.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/VoronovaLab3
)