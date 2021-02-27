FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_FILES LIST_DIRECTORIES true *.h *.cpp)

add_executable(tests ${TEST_FILES})
target_include_directories(tests PRIVATE ../src)
target_link_libraries(tests PRIVATE libpartgen gtest gtest_main gmock)
# target_clangformat_setup(tests)

include(GoogleTest)
gtest_discover_tests(tests)
