#include "rstd_test.hpp"
#include <rstd/assert.hpp>

#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>

namespace rstd::test {

struct InternalTest {
    std::string name{};
    TestFn func{nullptr};
};

static std::vector<InternalTest> gTests{};

void registerTest(const char* name, TestFn func) {
    gTests.emplace_back(InternalTest{name, func});
}

bool tryGetTest(const char* name, TestFn& outFunc) {
    for (auto& test : gTests) {
        if (test.name == name) {
            outFunc = test.func;
            return true;
        }
    }

    return false;
}

}

rstd::assert::AssertHandlerOutcome test_assert_handler(
    const char* msg, 
    const char* file, 
    const char* fn, 
    int line) {
        printf("Assertion failed: %s (%s:%d)\n", msg, file, line);
        exit(2);
        return rstd::assert::AssertHandlerOutcome::Abort;
}

int main(int argc, char* argv[]) {
    rstd::assert::setAssertionHandler(&test_assert_handler);

    if (argc >= 2) {
        rstd::test::TestFn t = nullptr;
        if (!rstd::test::tryGetTest(argv[1], t)) {
            fprintf(stderr, "Failed to find test \"%s\"\n", argv[1]);
            return -1;
        }
        return t() ? 0 : 1;
    } else {
        for (auto [name, fn] : rstd::test::gTests) {
            auto result = fn();
            std::printf("%s %s\n", name.c_str(), result ? "succeeded" : "failed");
        }
    }
}
