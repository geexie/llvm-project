add_llvm_component_library(LLVMKisozinovCount
	KisozinovCount.cpp

	DEPENDS
	intrinsics_gen

	COMPONENT_NAME
 	KisozinovCount

	LINK_COMPONENTS
	Core
	Support
	)
