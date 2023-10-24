cmake_minimum_required(VERSION 3.20)

project(
    FlowModel
    DESCRIPTION "Train and validate normalising flow models"
)

message(STATUS "Building ${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ...")

install(PROGRAMS bin/realnvp_postproc.py DESTINATION bin)