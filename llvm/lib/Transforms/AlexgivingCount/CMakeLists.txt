add_llvm_component_library(LLVMAlexgivingCount
 # .cpp files
 AlexgivingCount.cpp

 DEPENDS
 intrinsics_gen # to run table_gen on our target

 COMPONENT_NAME
 AlexgivingCount

 LINK_COMPONENTS
 Core # for structures
 Support # for errs
 )