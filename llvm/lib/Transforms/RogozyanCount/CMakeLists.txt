add_llvm_component_library(LLVMRogozyanCount
RogozyanCount.cpp

DEPENDS
intrinsics_gen

LINK_COMPONENTS
Core
Support
)
