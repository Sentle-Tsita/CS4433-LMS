cmake_minimum_required(VERSION 3.14)
project(LMS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lms src/main.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lms_tests tests/smoke_test.cpp)
target_link_libraries(lms_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lms_tests)