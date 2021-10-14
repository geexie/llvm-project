add_llvm_component_library(LLVMDBarinovCount
  DBarinovCount.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/DBarinovCount

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  DBarinovCount

  LINK_COMPONENTS
  Analysis
  Core
  Support
  )