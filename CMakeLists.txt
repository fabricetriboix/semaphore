cmake_minimum_required(VERSION 3.1)
project(semaphore)
enable_testing()

add_subdirectory(googletest)

config_compiler_and_linker()
add_test(NAME test-semaphore COMMAND test-semaphore)
add_executable(test-semaphore tests/test-semaphore.cpp)
target_include_directories(test-semaphore PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/safe_mutex/include)
target_link_libraries(test-semaphore gtest)
