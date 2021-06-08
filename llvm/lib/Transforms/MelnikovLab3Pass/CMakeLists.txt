add_llvm_component_library(LLVMMelnikovLab3Pass
MelnikovLab3Pass.cpp

DEPENDS 
intrinsics_gen

LINK_COMPONENTS
Core
Support
)