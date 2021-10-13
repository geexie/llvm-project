add_llvm_component_library(LLVMEugineerd
  Count.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/Eugineerd

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  Eugineerd

  LINK_COMPONENTS
  Analysis
  Core
  Support
  )
