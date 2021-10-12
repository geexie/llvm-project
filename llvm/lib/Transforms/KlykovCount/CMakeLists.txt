add_llvm_component_library(LLVMKlykovCount
  KlykovCount.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )