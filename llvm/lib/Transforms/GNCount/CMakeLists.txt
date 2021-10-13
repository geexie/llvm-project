add_llvm_component_library(LLVMGNCount
  GNCount.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )