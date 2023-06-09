cmake_minimum_required(VERSION 3.20)

project(
  Tufa
  VERSION 0.1
  DESCRIPTION
    "TUFA: Ttbar UnFolding Analysis"
  LANGUAGES CXX)

message(STATUS "Building ${CMAKE_PROJECT_NAME} ...")

# externals
add_subdirectory(RooUnfold)

# internals
add_subdirectory(ttbar_MadTree)
add_subdirectory(ttbar_Unfold)

set(CMAKE_INSTALL_PREFIX
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CXX_LIBRARY_ARCHITECTURE}-${CMAKE_CXX_COMPILER_VERSION}
)
