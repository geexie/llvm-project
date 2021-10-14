add_llvm_component_library(LLVMAlexeusC4ever
  AlexeusC4ever.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/AlexeusC4ever

  DEPENDS
  intrinsics_gen

  COMPONENT_NAME
  AlexeusC4ever

  LINK_COMPONENTS
  Analysis
  Core
  Support
  )