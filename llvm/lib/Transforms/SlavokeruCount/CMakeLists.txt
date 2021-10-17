add_llvm_component_library(LLVMSlavokeruCount
  SlavokeruCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  SlavokeruCount

  LINK_COMPONENTS
  Core
  Support
)