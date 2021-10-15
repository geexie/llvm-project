add_llvm_component_library(LLVMEkhorevCount
 	EkhorevCount.cpp

 	DEPENDS
 	intrinsics_gen

 	COMPONENT_NAME
  	EkhorevCount

 	LINK_COMPONENTS
 	Core
 	Support
 	)