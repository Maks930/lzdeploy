cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0167 OLD)
project(lzdeploy CXX)

set(CMAKE_CXX_STANDARD 20)


find_package(Boost COMPONENTS program_options REQUIRED)


file(GLOB_RECURSE SOURCES "src/*.cpp")

message("SOURCES")
message(${SOURCES})

add_executable(lzdeploy ${SOURCES})
target_link_libraries(lzdeploy PRIVATE Boost::program_options)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)