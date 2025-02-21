#pragma once

#include <rstd/types.hpp>
#include <rstd/memory/heap.hpp>

namespace rstd {

void* malloc(usize n) noexcept;
void* calloc(usize n, usize sz) noexcept;
void* realloc(void* p, usize n) noexcept;
void free(void* p) noexcept;

struct SystemHeap : public Heap {
    static SystemHeap* instance();
    
    void* alloc(usize n) override;
    void free(void* p) override;

    usize getHeapSize() const override;
    usize getMaxHeapSize() const override;
};

}