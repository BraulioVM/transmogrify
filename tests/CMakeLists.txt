find_package(GTest CONFIG REQUIRED)

include(GoogleTest)

add_executable(tests transmogrify.t.cpp)
target_link_libraries(tests
  PRIVATE GTest::gtest GTest::gtest_main transmogrify)


gtest_discover_tests(tests)

