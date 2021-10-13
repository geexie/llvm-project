add_llvm_component_library(LLVMSodaPass
SodaCount.cpp

DEPENDS
intrinsics_gen

COMPONENT_NAME
SodaCount

LINK_COMPONENTS
Core
Support
)
