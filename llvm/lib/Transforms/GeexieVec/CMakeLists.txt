add_llvm_component_library(LLVMGeexieVec
  GeexieVec.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )
