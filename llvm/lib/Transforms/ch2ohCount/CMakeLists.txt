add_llvm_component_library(LLVMch2ohCount
  ch2ohCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  ch2ohCount

  LINK_COMPONENTS
  Core
  Support
  )