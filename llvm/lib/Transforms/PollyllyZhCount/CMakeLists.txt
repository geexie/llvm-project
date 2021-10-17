add_llvm_component_library(LLVMPollyllyZhCount
PollyllyZhCount.cpp

DEPENDS
intrinsics_gen

LINK_COMPONENTS
Core
Support
)
