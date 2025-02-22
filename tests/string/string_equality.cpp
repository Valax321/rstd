#include <rstd/string.hpp>
#include "rstd_test.hpp"

using namespace rstd;

DECLARE_TEST(string_equal) {
    const char* s = "Hello, world!";
    String lhs(s);
    String rhs(s);

    return lhs == rhs;
}

DECLARE_TEST(string_not_equal) {
    const char* s = "Hello, world!";
    const char* s2 = "Goodbye, world!";
    String lhs(s);
    String rhs(s2);

    return lhs != rhs;
}

DECLARE_TEST(string_equal_fixed) {
    const char* s = "Hello, world!";
    String lhs(s);
    FixedString<128> rhs(s);

    return lhs == rhs;
}

DECLARE_TEST(string_not_equal_fixed) {
    const char* s = "Hello, world!";
    String lhs(s);
    FixedString<128> rhs(s);

    return lhs == rhs;
}

DECLARE_TEST(fixed_equal_fixed) {
    const char* s = "Hello, world!";
    FixedString<128> lhs(s);
    FixedString<128> rhs(s);

    return lhs == rhs;
}

DECLARE_TEST(fixed_not_equal_fixed) {
    const char* s = "Hello, world!";
    const char* s2 = "Goodbye, world!";
    FixedString<128> lhs(s);
    FixedString<128> rhs(s2);

    return lhs != rhs;
}
