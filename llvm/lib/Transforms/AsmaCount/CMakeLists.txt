dd_llvm_component_library(LLVMAsmaCount
  AsmaCount.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )
