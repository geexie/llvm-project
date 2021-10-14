add_llvm_component_library(LLVMAnyaSchenCount
  AnyaSchenCount.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )