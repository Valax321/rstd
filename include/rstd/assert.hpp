#pragma once

#include <rstd/types.hpp>
#include <rstd/detail/debugbreak.h>

namespace rstd::assert {

enum class AssertHandlerOutcome {
    Abort,
    Ignore,
    Break
};

using AssertHandlerFn = AssertHandlerOutcome (*)(const char* msg, const char* file, const char* fn, int line);

void setAssertionHandler(AssertHandlerFn callback);
AssertHandlerFn getAssertionHandler();

[[noreturn]]
void doAbort();

}

#ifdef RADISH_ENABLE_ASSERTIONS

#define RADISH_ASSERT(x)                                                                                \
do {                                                                                                    \
    if (!(x)) {                                                                                         \
        auto result = rstd::assert::getAssertionHandler()(#x, __FILE__, __FUNCTION__, __LINE__);        \
        switch (result) {                                                                               \
            case rstd::assert::AssertHandlerOutcome::Abort:                                             \
            rstd::assert::doAbort();                                                                    \
            break;                                                                                      \
            case rstd::assert::AssertHandlerOutcome::Ignore:                                            \
            break;                                                                                      \
            case rstd::assert::AssertHandlerOutcome::Break:                                             \
            debug_break();                                                                              \
            break;                                                                                      \
        }                                                                                               \
    }                                                                                                   \
} while (0)

#define RADISH_ASSERT_MSG(x, msg)                                                                       \
do {                                                                                                    \
    if (!(x)) {                                                                                         \
        auto result = rstd::assert::getAssertionHandler()((msg), __FILE__, __FUNCTION__, __LINE__);     \
        switch (result) {                                                                               \
            case rstd::assert::AssertHandlerOutcome::Abort:                                             \
            rstd::assert::doAbort();                                                                    \
            break;                                                                                      \
            case rstd::assert::AssertHandlerOutcome::Ignore:                                            \
            break;                                                                                      \
            case rstd::assert::AssertHandlerOutcome::Break:                                             \
            debug_break();                                                                              \
            break;                                                                                      \
        }                                                                                               \
    }                                                                                                   \
} while (0)

#else

#define RADISH_ASSERT(x) do { (void)0; } while(0)
#define RADISH_ASSERT_MSG(x, msg) do { (void)0; } while(0)

#endif
