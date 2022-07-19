# Copyright (C) Tommy Hinks <tommy.hinks@gmail.com>
# This file is subject to the license terms in the LICENSE file
# found in the top-level directory of this distribution.

cmake_minimum_required(VERSION 3.11)

# Set BUILD_TESTING to OFF by default.
# This must come before the project() and include(CTest) lines.
# option(BUILD_TESTING "Build tests" OFF)
# option(BUILD_STATIC_TESTING "Build static tests" OFF)
# option(WARNINGS_AS_ERRORS "Warnings as errors" OFF)

##
## PROJECT
## Name and version.
##
project(tph_linalg VERSION 0.1.0 LANGUAGES CXX)
message(STATUS "CMake version: ${CMAKE_VERSION}")

##
## MAIN PROJECT CHECK
## Determine if tph_linalg is built as a subproject (using add_subdirectory) 
## or if it is the main project.
##
set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MAIN_PROJECT ON)
endif()

##
## INCLUDE
##
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
#include(FetchContent)

##
## OPTIONS
##
if (POLICY CMP0077)
  # Allow CMake 3.13+ to override options when using FetchContent / add_subdirectory.
  cmake_policy(SET CMP0077 NEW)
endif ()

# VERSION_GREATER_EQUAL is not available in CMake 3.1
if(${MAIN_PROJECT} AND (${CMAKE_VERSION} VERSION_EQUAL 3.13 OR ${CMAKE_VERSION} VERSION_GREATER 3.13))
  set(TPH_BuildTests_INIT ON)
else()
  set(TPH_BuildTests_INIT OFF)
endif()

option(TPH_BuildTests     "Build the unit tests when BUILD_TESTING is enabled." ${TPH_BuildTests_INIT})
option(TPH_Install        "Install CMake targets during install step." ${MAIN_PROJECT})
option(TPH_SystemInclude  "Include as system headers (skip for clang-tidy)." OFF)

## 
## CONFIGURATION
##
include(GNUInstallDirs)

set(TPH_LINALG_TARGET_NAME                 ${PROJECT_NAME})
set(TPH_LINALG_CONFIG_INSTALL_DIR          "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(TPH_LINALG_INCLUDE_BUILD_DIR           "${PROJECT_SOURCE_DIR}/include/")
set(TPH_LINALG_INCLUDE_INSTALL_DIR         "${CMAKE_INSTALL_INCLUDEDIR}")
set(TPH_LINALG_TARGETS_EXPORT_NAME         "${PROJECT_NAME}Targets")
set(TPH_LINALG_CMAKE_CONFIG_TEMPLATE       "cmake/config.cmake.in")
set(TPH_LINALG_CMAKE_CONFIG_DIR            "${CMAKE_CURRENT_BINARY_DIR}")
set(TPH_LINALG_CMAKE_VERSION_CONFIG_FILE   "${TPH_LINALG_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(TPH_LINALG_CMAKE_PROJECT_CONFIG_FILE   "${TPH_LINALG_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(TPH_LINALG_CMAKE_PROJECT_TARGETS_FILE  "${TPH_LINALG_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")
set(TPH_LINALG_PKGCONFIG_INSTALL_DIR       "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

if (TPH_SystemInclude)
  set(TPH_LINALG_SYSTEM_INCLUDE "SYSTEM")
endif()

##
## TARGET
## Create target and add include path.
##
add_library(${TPH_LINALG_TARGET_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${TPH_LINALG_TARGET_NAME} ALIAS ${TPH_LINALG_TARGET_NAME})
if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
  target_compile_features(${TPH_LINALG_TARGET_NAME} INTERFACE cxx_range_for)
else()
  target_compile_features(${TPH_LINALG_TARGET_NAME} INTERFACE cxx_std_11)
endif()

target_include_directories(${TPH_LINALG_TARGET_NAME}
  ${TPH_LINALG_SYSTEM_INCLUDE} INTERFACE
  $<BUILD_INTERFACE:${TPH_LINALG_INCLUDE_BUILD_DIR}>
  $<INSTALL_INTERFACE:include>
)

# Install a pkg-config file, so other tools can find this.
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/pkg-config.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
)

##
## TESTS
## Create and configure the test target.
##
if (TPH_BuildTests)
  # We only have static tests (build-time), so we don't need to enable CTest.
  # If the tests build successfully that is proof enough that they pass, no
  # need to run anything.
  add_subdirectory(tests)
endif()

##
## INSTALL
## Install header files, generate and install cmake config files for find_package().
##
include(CMakePackageConfigHelpers)
# Use a custom package version config file instead of
# write_basic_package_version_file to ensure that it's architecture-independent.
configure_file(
  "cmake/tph_linalgConfigVersion.cmake.in"
  ${TPH_LINALG_CMAKE_VERSION_CONFIG_FILE}
  @ONLY
)
configure_file(
  ${TPH_LINALG_CMAKE_CONFIG_TEMPLATE}
  ${TPH_LINALG_CMAKE_PROJECT_CONFIG_FILE}
  @ONLY
)

if(TPH_Install)
  install(
    DIRECTORY ${TPH_LINALG_INCLUDE_BUILD_DIR}
    DESTINATION ${TPH_LINALG_INCLUDE_INSTALL_DIR}
  )
  install(
    FILES ${TPH_LINALG_CMAKE_PROJECT_CONFIG_FILE} ${TPH_LINALG_CMAKE_VERSION_CONFIG_FILE}
    DESTINATION ${TPH_LINALG_CONFIG_INSTALL_DIR}
  )
  export(
    TARGETS ${TPH_LINALG_TARGET_NAME}
    NAMESPACE ${PROJECT_NAME}::
    FILE ${TPH_LINALG_CMAKE_PROJECT_TARGETS_FILE}
  )
  install(
    TARGETS ${TPH_LINALG_TARGET_NAME}
    EXPORT ${TPH_LINALG_TARGETS_EXPORT_NAME}
    INCLUDES DESTINATION ${TPH_LINALG_INCLUDE_INSTALL_DIR}
  )
  install(
    EXPORT ${TPH_LINALG_TARGETS_EXPORT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${TPH_LINALG_CONFIG_INSTALL_DIR}
  )
  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
    DESTINATION ${TPH_LINALG_PKGCONFIG_INSTALL_DIR}
  )
endif()
