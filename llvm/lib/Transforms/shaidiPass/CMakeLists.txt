add_llvm_component_library(LLVMshaidiPass
  shaidiPass.cpp

  DEPENDS
  intrinsics_gen # to run table_gen on our target

  COMPONENT_NAME
  shaidiPass

  LINK_COMPONENTS
  Core # for structures
  Support # for errs
  ) 
