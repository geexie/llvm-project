add_llvm_component_library(LLVMKuznetsovMikhailCount
  KuznetsovMikhailCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  KuznetsovMikhailCount

  LINK_COMPONENTS
  Core
  Support
  )