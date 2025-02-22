#include <rstd/string.hpp>
#include <rstd/assert.hpp>
#include "rstd_test.hpp"

#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace rstd;

DECLARE_TEST(string_append_string) {
    String r1("hello, ");
    String r2("world!");

    r1 += r2;

    if (std::strcmp(r1.cstr(), "hello, world!") != 0)
        return false;

    return true;
}

DECLARE_TEST(string_append_charptr) {
    String r1("hello, ");

    r1 += "world!";

    if (std::strcmp(r1.cstr(), "hello, world!") != 0)
        return false;

    return true;
}

DECLARE_TEST(string_append_fixed) {
    String r1("hello, ");
    FixedString<128> r2("world!");

    r1 += r2;

    if (std::strcmp(r1.cstr(), "hello, world!") != 0)
        return false;

    return true;
}

DECLARE_TEST(string_appended_size) {
    auto s = "hello, world!";
    String r1("hello, ");
    String r2("world!");

    r1 += r2;

    if (r1.length() != strlen(s))
        return false;

    return true;
}

DECLARE_TEST(string_length) {
    auto s = "hello, world!";
    String r1(s);
    if (r1.length() != strlen(s))
        return false;

    return true;
}

DECLARE_TEST(string_size) {
    auto s = "hello, world!";
    String r1(s);
    if (r1.size() != (strlen(s) + 1))
        return false;

    return true;
}

DECLARE_TEST(string_ensure_size) {
    String r1("hello, world!");
    r1.ensureSize(32);
    if (r1.size() < 32)
        return false;

    return true;
}
