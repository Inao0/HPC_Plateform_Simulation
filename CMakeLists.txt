cmake_minimum_required(VERSION 3.15)
project(SuperComputerSimulation)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ./bin)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES ./src/main.cpp src/factorial.cpp )
set(TESTS_FILES tests/tests-main.cpp tests/factorial-test.cpp)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(./tests)
endif()

add_compile_options(-Wpedantic)

add_executable(SuperComputerSimulation ${SOURCE_FILES})


