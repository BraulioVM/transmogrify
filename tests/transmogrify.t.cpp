#include <transmogrify.h>

#include <gtest/gtest.h>

#define BASIC_MOCK(name) \
    bool name##_called = false; \
    void name() { name##_called = true; }

BASIC_MOCK(target_function);
BASIC_MOCK(hook_function);

TEST(TransmogrifyTests, BasicTest) {
    // GIVEN
    ASSERT_TRUE(transmogrify::hook(&target_function, &hook_function));

    // WHEN
    target_function();

    // THEN
    EXPECT_TRUE(hook_function_called);
    EXPECT_TRUE(target_function_called);
}

BASIC_MOCK(target_function_1);
BASIC_MOCK(target_function_2);
BASIC_MOCK(target_function_3);
BASIC_MOCK(target_function_4);
BASIC_MOCK(hook_1);
BASIC_MOCK(hook_2);
BASIC_MOCK(hook_3);
BASIC_MOCK(hook_4);

TEST(TransmogrifyHooks, canSetMultipleHooks)
{
    // GIVEN
    ASSERT_TRUE(transmogrify::hook(&target_function_1, hook_1));
    ASSERT_TRUE(transmogrify::hook(&target_function_2, hook_2));

    // WHEN
    target_function_1();

    // THEN
    EXPECT_TRUE(target_function_1_called);
    EXPECT_TRUE(hook_1_called);
    EXPECT_FALSE(target_function_2_called);
    EXPECT_FALSE(hook_2_called);

    // AND WHEN
    target_function_2();

    // THEN
    EXPECT_TRUE(target_function_2_called);
    EXPECT_TRUE(hook_2_called);
}

TEST(TransmogrifyHooks, canSet4Hooks)
{
    // GIVEN
    ASSERT_TRUE(transmogrify::hook(&target_function_1, hook_1));
    ASSERT_TRUE(transmogrify::hook(&target_function_2, hook_2));
    ASSERT_TRUE(transmogrify::hook(&target_function_3, hook_3));
    ASSERT_TRUE(transmogrify::hook(&target_function_4, hook_4));

    // WHEN
    target_function_1();
    target_function_2();
    target_function_3();
    target_function_4();

    // THEN
#define EXPECT_WAS_CALLED(num) \
    EXPECT_TRUE(target_function_##num##_called); \
    EXPECT_TRUE(hook_##num##_called);

    EXPECT_WAS_CALLED(1);
    EXPECT_WAS_CALLED(2);
    EXPECT_WAS_CALLED(3);
    EXPECT_WAS_CALLED(4);
#undef EXPECT_WAS_CALLED
}

