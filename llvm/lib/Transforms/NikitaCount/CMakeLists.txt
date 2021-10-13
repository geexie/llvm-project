add_llvm_component_library(LLVMNikitaCount
  NikitaCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  NikitaCount

  LINK_COMPONENTS
  Core
  Support
)