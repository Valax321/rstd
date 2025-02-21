#include <rstd/assert.hpp>

#include <cstdlib>

namespace rstd::assert {

static AssertHandlerFn gAssertionHandler{nullptr};

void setAssertionHandler(AssertHandlerFn callback) {
    gAssertionHandler = callback;
}

AssertHandlerFn getAssertionHandler() {
    return gAssertionHandler;
}

void doAbort() {
    abort();
}

}
