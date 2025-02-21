#pragma once

#include <rstd/types.hpp>

namespace rstd {

struct Heap {
    virtual ~Heap() = default;

    virtual void* alloc(usize n) = 0;
    virtual void free(void* p) = 0;

    virtual usize getHeapSize() const = 0;
    virtual usize getMaxHeapSize() const = 0;
};

}
