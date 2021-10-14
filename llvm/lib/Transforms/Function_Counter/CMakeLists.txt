add_llvm_component_library(LLVMFunction_counter
 # .cpp files
 Function_counter.cpp

 DEPENDS
 intrinsics_gen # to run table_gen on our target

 COMPONENT_NAME
 Function_counter

 LINK_COMPONENTS
 Core # for structures
 Support # for errs
 )