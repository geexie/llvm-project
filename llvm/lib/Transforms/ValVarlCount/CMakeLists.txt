add_llvm_component_library(LLVMValVarlCount
  ValVarlCount.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )