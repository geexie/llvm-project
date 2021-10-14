add_llvm_component_library(LLVMVadukklab1
Vadukklab1.cpp

DEPENDS
intrinsics_gen

COMPONENT_NAME
Vadukklab1

LINK_COMPONENTS
Core
Support
)