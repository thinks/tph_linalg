# Copyright (C) Tommy Hinks <tommy.hinks@gmail.com>
# This file is subject to the license terms in the LICENSE file
# found in the top-level directory of this distribution.

add_executable(tests_main "static_tests.cpp")
target_compile_features(tests_main PRIVATE cxx_std_11)
target_compile_options(tests_main 
  PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/EHsc;$<$<CONFIG:Release>:/Od>>
    # MSVC: Force to always compile with W4
    $<$<CXX_COMPILER_ID:MSVC>:/W4>

    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-deprecated;-Wno-float-equal>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
)
target_link_libraries(tests_main 
  PRIVATE 
    ${TPH_LINALG_TARGET_NAME}
)

# Set and require C++ standard.
set_target_properties(tests_main PROPERTIES
  CXX_STANDARD ${CMAKE_CXX_STANDARD}
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
