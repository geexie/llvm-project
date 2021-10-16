add_llvm_component_library(LLVMBulatovDmitriyCount
  BulatovDmitriyCount.cpp

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  BulatovDmitriyCount

  LINK_COMPONENTS
  Core
  Support
  )
