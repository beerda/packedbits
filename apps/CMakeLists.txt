add_compile_options(
    -march=native -mtune=native
)

add_executable(packedbits main.cpp)
target_link_libraries(packedbits PRIVATE packedbits_lib benchmark::benchmark Boost::headers)

add_executable(unittest
    unittest_dummy.cpp
)
target_link_libraries(unittest PRIVATE packedbits_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unittest)
