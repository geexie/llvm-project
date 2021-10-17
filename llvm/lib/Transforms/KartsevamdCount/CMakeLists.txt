add_llvm_component_library(LLVMKartsevamdCount
  KartsevamdCount.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )