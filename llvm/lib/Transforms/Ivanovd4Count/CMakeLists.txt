add_llvm_component_library(LLVMIvanovd4Count
  Ivanovd4Count.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )