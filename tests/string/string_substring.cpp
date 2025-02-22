#include <rstd/string.hpp>
#include "rstd_test.hpp"

using namespace rstd;

DECLARE_TEST(substring_indexed) {
    String s("Hello, world!");

    return s.substring(0, 5) == "Hello";
}
