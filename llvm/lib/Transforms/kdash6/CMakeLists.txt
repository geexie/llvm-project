add_llvm_component_library(LLVMkdash6
  kdash6.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )
