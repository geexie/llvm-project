add_llvm_component_library(LLVMEgorovaCount
  EgorovaCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  EgorovaCount

  LINK_COMPONENTS
  Core
  Support
  ) 