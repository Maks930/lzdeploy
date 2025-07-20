cmake_minimum_required(VERSION 3.10)
project(lzdeploy CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(lzdeploy ${SOURCES})