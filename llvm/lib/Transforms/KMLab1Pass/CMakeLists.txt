add_llvm_component_library(LLVMKMLab1Pass
KMLab1Pass.cpp

DEPENDS 
intrinsics_gen

LINK_COMPONENTS
Core
Support
) 