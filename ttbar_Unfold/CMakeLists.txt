cmake_minimum_required(VERSION 3.20)

project(
  ttbar_Unfold
  DESCRIPTION "Analyze histograms using RooUnfold"
  LANGUAGES CXX)

message(STATUS "Building ${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ...")

find_package(ROOT REQUIRED COMPONENTS ${rootlibs})

include_directories(SYSTEM ${ROOT_INCLUDE_DIRS})
include_directories(include/)
link_directories(${ROOT_LIBRARY_DIR})

file(GLOB UNFOLD_SRC src/*.cpp)
file(GLOB UNFOLD_INC src/*.hpp)

add_library(${PROJECT_NAME} SHARED ${UNFOLD_SRC} ${UNFOLD_INC})
target_link_libraries(${PROJECT_NAME} PRIVATE RooUnfold)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${UNFOLD_INC} DESTINATION include)

add_executable(Tutorial external/tutorial.cpp)
target_link_libraries(Tutorial PRIVATE ${PROJECT_NAME} RooUnfold)

add_executable(Unfold utils/main.cpp)
target_link_libraries(Unfold PRIVATE ${PROJECT_NAME} RooUnfold)

install(TARGETS Tutorial Unfold RUNTIME DESTINATION bin)

add_test(NAME Tutorial_Testing COMMAND Tutorial && rm -f *png)