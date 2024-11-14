enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(IPTest test_ip.cpp)
target_link_libraries(IPTest
    types
    # gtest gtest_main
    GTest::GTest GTest::Main
)

# https://cmake.org/cmake/help/latest/module/GoogleTest.html#command:gtest_discover_tests
# gtest_add_tests(TARGET IPTest
gtest_discover_tests(IPTest
    # TEST_SUFFIX .noArgs
    # EXTRA_ARGS  --someArg someValue
    # TEST_LIST   noArgsTests
)

set_tests_properties(${noArgsTests}
   PROPERTIES TIMEOUT 10)
