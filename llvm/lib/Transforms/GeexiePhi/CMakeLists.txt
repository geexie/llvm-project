add_llvm_component_library(LLVMGeexiePhi
  GeexiePhi.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )
