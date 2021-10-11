add_llvm_component_library(LLVMAHabKaffeeCount
 # .cpp files
 HabKaffeeCount.cpp

 DEPENDS
 intrinsics_gen # to run table_gen on our target

 COMPONENT_NAME
 HabKaffeeCount

 LINK_COMPONENTS
 Core # for structures
 Support # for errs
 ) 