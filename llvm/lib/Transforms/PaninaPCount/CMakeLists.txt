add_llvm_component_library(LLVMPaninaPCount
  PaninaPCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  PaninaPCount

  LINK_COMPONENTS
  Core
  Support
  )