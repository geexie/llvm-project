add_llvm_component_library(LLVMDenisKabanov
# .cpp files
DenisKabanov.cpp

DEPENDS
intrinsics_gen

COMPONENT_NAME
DenisKabanov

LINK_COMPONENTS
Core
Support
)
