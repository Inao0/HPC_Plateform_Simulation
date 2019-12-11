cmake_minimum_required(VERSION 3.15)
project(SuperComputerSimulation)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ./bin)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES ./src/main.cpp src/factorial.cpp )
set(TESTS_FILES tests/tests-main.cpp tests/factorial-test.cpp)

add_compile_options(-Wpedantic)
add_executable(SuperComputerSimulation ${SOURCE_FILES})
add_executable(SuperComputerSimulationTests ${TESTS_FILES})

