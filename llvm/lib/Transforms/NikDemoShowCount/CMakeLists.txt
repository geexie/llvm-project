add_llvm_component_library(LLVMNikDemoShowCount
  NikDemoShowCount.cpp
  
  DEPENDS
  intrinsics_gen
  
  COMPONENT_NAME
  NikDemoShowCount
  
  LINK_COMPONENTS
  Core
  Support
  )
