add_llvm_component_library(LLVMKisozinovCount
	KisozinovCount.cpp

	DEPENDS
	intrinsics_gen

	LINK_COMPONENTS
	Core
	Support
	)
