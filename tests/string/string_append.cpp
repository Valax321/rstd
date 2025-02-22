#include <rstd/string.hpp>
#include <rstd/assert.hpp>

#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace rstd;

assert::AssertHandlerOutcome test_assert_handler(
    const char* msg, 
    const char* file, 
    const char* fn, 
    int line) {
        printf("Assertion failed: %s (%s:%d)\n", msg, file, line);
        exit(-1);
        return assert::AssertHandlerOutcome::Abort;
}

int append_string_to_string() {
    String r1("hello, ");
    String r2("world!");

    r1 += r2;

    if (std::strcmp(r1.cstr(), "hello, world!") != 0)
        return 1;

    return 0;
}

int append_charptr_to_string() {
    String r1("hello, ");

    r1 += "world!";

    if (std::strcmp(r1.cstr(), "hello, world!") != 0)
        return 1;

    return 0;
}

int append_fixed_to_string() {
    String r1("hello, ");
    FixedString<128> r2("world!");

    r1 += r2;

    if (std::strcmp(r1.cstr(), "hello, world!") != 0)
        return 1;

    return 0;
}

int check_append_length() {
    auto s = "hello, world!";
    String r1("hello, ");
    String r2("world!");

    r1 += r2;

    if (r1.length() != strlen(s))
        return 1;

    return 0;
}

int check_length() {
    auto s = "hello, world!";
    String r1(s);
    if (r1.length() != strlen(s))
        return 1;

    return 0;
}

int check_size() {
    auto s = "hello, world!";
    String r1(s);
    if (r1.size() != (strlen(s) + 1))
        return 1;

    return 0;
}

int check_ensure_size() {
    String r1("hello, world!");
    r1.ensureSize(32);
    if (r1.size() < 32)
        return 1;

    return 0;
}

using test_fn = int (*)(void);

const test_fn gTests[] = {
    &append_string_to_string,
    &append_charptr_to_string,
    &append_fixed_to_string,
    &check_length,
    &check_size,
    &check_ensure_size,
    &check_append_length
};

constexpr auto gTestsCount = sizeof(gTests) / sizeof(gTests[0]);

int main(int argc, char* argv[]) {
    assert::setAssertionHandler(&test_assert_handler);

    if (argc >= 2) {
        auto idx = std::atoi(argv[1]);
        return gTests[idx]();
    } else {
        for (auto i = 0; i < gTestsCount; ++i) {
            auto result = gTests[i]();
            printf("Test %d returned %d\n", i, result == 0);
        }
    }
}