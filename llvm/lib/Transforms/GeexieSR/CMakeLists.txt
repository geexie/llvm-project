add_llvm_component_library(LLVMGeexieSR
  GeexieSR.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )
