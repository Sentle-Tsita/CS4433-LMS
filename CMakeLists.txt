cmake_minimum_required(VERSION 3.14)
project(LMS LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lms_core src/StandardLatePenalty.cpp)
target_include_directories(lms_core PUBLIC src)

add_executable(lms src/main.cpp)
target_link_libraries(lms PRIVATE lms_core)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_Declare(
  sodium
  GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
  GIT_TAG        9b2848dfc1b917a9410f0de9d81059b26cbfaa8d
)
set(SODIUM_DISABLE_TESTS ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest sodium)

enable_testing()
add_executable(lms_tests tests/smoke_test.cpp tests/libsodium_trial_test.cpp tests/standard_late_penalty_test.cpp)
target_link_libraries(lms_tests PRIVATE lms_core GTest::gtest_main sodium)

include(GoogleTest)
gtest_discover_tests(lms_tests)