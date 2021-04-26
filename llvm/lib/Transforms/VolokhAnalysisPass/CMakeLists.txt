add_llvm_component_library( LLVMVolokhAnalysisPass
  VolokhAnalysisPass.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/VolokhAnalysisPass

) 