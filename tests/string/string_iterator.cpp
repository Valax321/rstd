#include <rstd/string.hpp>
#include <rstd/assert.hpp>
#include "rstd_test.hpp"

#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace rstd;

constexpr auto TEST_STRING = "abcdefABCDEF";
constexpr auto TEST_STRING_END = "bcdefgBCDEFG";

DECLARE_TEST(string_iterator_manual) {
    String s(TEST_STRING);
    int itrCount = 0;
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
        char& c = *itr;
        c++;
        printf("%c", c);
        itrCount++;
    }
    printf("\n");

    if (itrCount != s.length())
        return false;

    return true;
}

DECLARE_TEST(string_iterator_manual_const) {
    const String s(TEST_STRING);
    int itrCount = 0;
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
        auto& c = *itr;
        printf("%c", c);
        itrCount++;
    }
    printf("\n");

    if (itrCount != s.length())
        return false;

    return true;
}

DECLARE_TEST(string_iterator_auto) {
    String s(TEST_STRING);
    int itrCount = 0;
    for (auto& c : s) {
        c++;
        printf("%c", c);
        itrCount++;
    }
    printf("\n");

    if (itrCount != s.length())
        return false;

    return true;
}

DECLARE_TEST(string_iterator_auto_const) {
    const String s(TEST_STRING);
    int itrCount = 0;
    for (const auto& c : s) {
        printf("%c", c);
        itrCount++;
    }
    printf("\n");

    if (itrCount != s.length())
        return false;

    return true;
}

DECLARE_TEST(string_iterator_arrayop) {
    String s(TEST_STRING);
    for (auto i = 0; i < s.length(); ++i)
    {
        auto& c = s[i];
        c++;
        printf("%c", c);
    }

    printf("\n");

    if (s != String(TEST_STRING_END))
        return false;

    return true;
}

DECLARE_TEST(string_iterator_at) {
    String s(TEST_STRING);
    auto itr = s.at(3);
    return *itr == 'd';
}

DECLARE_TEST(string_arrayop_at) {
    String s(TEST_STRING);
    auto c = s[3];
    return c == 'd';
}
