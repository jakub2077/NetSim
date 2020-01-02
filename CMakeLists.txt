cmake_minimum_required(VERSION 3.13)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

set(SOURCE_FILES
        src/storage_types.cpp
        src/package.cpp
        src/nodes.cpp
        src/helpers.cpp)


add_executable(NetSim main.cpp ${SOURCE_FILES})

# == Unit testing using Google Testing Framework ==

set(SOURCES_FILES_TESTS
        tests/package_tests.cpp
        tests/storage_tests.cpp
        tests/nodes_tests.cpp)

add_executable(NetSim__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} tests/main_gtest.cpp)

target_include_directories(NetSim__test PUBLIC
        ../googletest-master/googlemock/include
        ../googletest-master/googletest/include
        )

add_subdirectory(../googletest-master googletest-master)

target_link_libraries(NetSim__test gmock)