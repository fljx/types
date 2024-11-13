include(GoogleTest)

add_executable(IPTest test_ip.cpp)
gtest_add_tests(TARGET      IPTest
    TEST_SUFFIX .noArgs
    # EXTRA_ARGS  --someArg someValue
    TEST_LIST   noArgsTests
)

set_tests_properties(${noArgsTests}
   PROPERTIES TIMEOUT 10)
