add_llvm_component_library(LLVMEliseTorbaCount
EliseTorbaCount.cpp

DEPENDS
intrinsics_gen

LINK_COMPONENTS
Core
Support
)
