cmake_minimum_required(VERSION 3.15)
project(murmur CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    socpp
    GIT_REPOSITORY https://github.com/Davis-Reis/socpp.git
    GIT_TAG main
)
FetchContent_MakeAvailable(socpp)

enable_testing()
add_executable(test_serialize tests/test_serialize.cpp src/serialize.cpp)
add_executable(test_framing tests/test_framing.cpp src/framing.cpp)
target_include_directories(test_serialize PRIVATE include/murmur)
target_include_directories(test_framing PRIVATE include/murmur)
target_link_libraries(test_framing PRIVATE socpp)
add_test(NAME serialize COMMAND test_serialize)
add_test(NAME framing COMMAND test_framing)
