add_llvm_component_library(LLVMKarinaMCount
  KarinaMCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  KarinaMCount

  LINK_COMPONENTS
  Core
  Support
  )
