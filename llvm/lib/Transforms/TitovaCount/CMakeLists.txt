add_llvm_component_library(LLVMTitovaCount
TitovaCount.cpp

DEPENDS
intrinsics_gen

LINK_COMPONENTS
Core
Support
)
