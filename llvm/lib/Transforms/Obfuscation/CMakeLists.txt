add_llvm_component_library(LLVMObfuscation
  CryptoUtils.cpp
  Substitution.cpp
  StringObfuscation.cpp
  BogusControlFlow.cpp
  Utils.cpp
  SplitBasicBlocks.cpp
  Flattening.cpp
  //LegacyPMRegistration.cpp
  //NewPMRegistration.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/Obfuscation

  DEPENDS
  intrinsics_gen
)

# # Use C++11 to compile your pass (i.e., supply -std=c++11).
# target_compile_features(LLVMObfuscation PRIVATE cxx_range_for cxx_auto_type)

# # LLVM is (typically) built with no C++ RTTI. We need to match that;
# # otherwise, we'll get linker errors about missing RTTI data.
# set_target_properties(LLVMObfuscation PROPERTIES
#     COMPILE_FLAGS "-fno-rtti"
# )

# if(APPLE)
#     set_target_properties(LLVMObfuscation PROPERTIES
#         LINK_FLAGS "-undefined dynamic_lookup"
#     )
# endif(APPLE)