#pragma once

namespace rstd::test {

using TestFn = bool (*)(void);

void registerTest(const char* name, TestFn func);
bool tryGetTest(const char* name, TestFn& outFunc);

struct Test {
    Test(const char* name, TestFn func) {
        registerTest(name, func);
    }
};

}

#define DECLARE_TEST(name)                                      \
bool TestFunc_##name();                                         \
static rstd::test::Test Test_##name{#name, &TestFunc_##name};   \
bool TestFunc_##name()
