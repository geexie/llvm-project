add_llvm_component_library(LLVMBogomazovCountPass
BogomazovCount.cpp

DEPENDS
intrinsics_gen

COMPONENT_NAME
BogomazovCount

LINK_COMPONENTS
Core
Support
)
