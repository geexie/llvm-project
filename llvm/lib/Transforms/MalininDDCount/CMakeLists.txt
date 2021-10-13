add_llvm_component_library(LLVMMalininDDCount
 # .cpp files
 MalininDDCount.cpp

 DEPENDS
 intrinsics_gen # to run table_gen on our target

 COMPONENT_NAME
 MalininDDCount

 LINK_COMPONENTS
 Core # for structures
 Support # for errs
 ) 