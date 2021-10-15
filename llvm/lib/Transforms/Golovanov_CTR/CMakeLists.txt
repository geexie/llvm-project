add_llvm_component_library(LLVMGolovanov_CTR
 Golovanov_CTR.cpp

 DEPENDS
 intrinsics_gen 

 COMPONENT_NAME
 Golovanov_CTR

 LINK_COMPONENTS
 Core 
 Support 
 ) 
