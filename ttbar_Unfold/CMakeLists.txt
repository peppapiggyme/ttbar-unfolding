cmake_minimum_required(VERSION 3.20)

project(
  ttbar_Unfold
  DESCRIPTION "Analyze histograms using RooUnfold"
  LANGUAGES CXX)

message(STATUS "Building ${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ...")

find_package(ROOT REQUIRED COMPONENTS ${rootlibs})

include_directories(SYSTEM ${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARY_DIR})

add_executable(Tutorial external/tutorial.cpp)
target_link_libraries(Tutorial PRIVATE RooUnfold)

add_executable(Unfold utils/main.cpp)
target_link_libraries(Unfold PRIVATE RooUnfold)

install(TARGETS Tutorial Unfold RUNTIME DESTINATION bin)
