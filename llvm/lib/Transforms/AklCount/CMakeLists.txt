add_llvm_component_library(LLVMAklCount
  AklCount.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )