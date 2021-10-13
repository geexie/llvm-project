add_llvm_component_library(LLVMLongaBongaCount
  # .cpp files
  LongaBongaCount.cpp

  DEPENDS
  intrinsics_gen # to run table_gen on our target

  COMPONENT_NAME
  LongaBongaCount

  LINK_COMPONENTS
  Core # for structures
  Support # for errs
  )