#include <transmogrify.h>

#include <gtest/gtest.h>

bool target_function_called = false;
bool hook_function_called = false;

void target_function() {
    target_function_called = true;
}

void hook_function() {
    hook_function_called = true;
}

TEST(TransmogrifyTests, BasicTest) {
    // GIVEN
    ASSERT_TRUE(transmogrify::hook(&target_function, &hook_function));

    // WHEN
    target_function();

    // THEN
    EXPECT_TRUE(hook_function_called);
    EXPECT_TRUE(target_function_called);
}
