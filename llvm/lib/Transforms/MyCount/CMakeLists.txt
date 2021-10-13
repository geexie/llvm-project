add_llvm_component_library(LLVMMyCount
  MyCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  MyCount

  LINK_COMPONENTS
  Core
  Support
  )