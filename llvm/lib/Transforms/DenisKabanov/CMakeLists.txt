add_llvm_component_library(LLVMDenisKabanov
# .cpp files
DenisKabanov.cpp

DEPENDS
intrinsics_gen # to run table_gen on our target

COMPONENT_NAME
DenisKabanov

LINK_COMPONENTS
Core # for structures
Support # for errs
)
