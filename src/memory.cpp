#include "rstd/memory.hpp"
#include "rstd/memory/heap.hpp"
#include "rstd/memory/malloc.hpp"
#include "rstd/assert.hpp"

#include <memory>

#pragma region System Memory Allocators
namespace rstd {

static SystemHeap gSystemHeap{};

void* malloc(usize n) noexcept {
    return std::malloc(n);
}

void* calloc(usize n, usize sz) noexcept {
    return std::calloc(n, sz);
}

void* realloc(void* p, usize n) noexcept {
    return std::realloc(p, n);
}

void free(void* p) noexcept {
    std::free(p);
}

SystemHeap* rstd::SystemHeap::instance() { return &gSystemHeap; }

void* rstd::SystemHeap::alloc(usize n) {
    return rstd::malloc(n);
}

void rstd::SystemHeap::free(void* p) {
    rstd::free(p);
}

usize rstd::SystemHeap::getHeapSize() const
{
    return USIZE_MAX;
}

usize rstd::SystemHeap::getMaxHeapSize() const
{
    return USIZE_MAX;
}

}
#pragma endregion

#pragma region Global New/Delete

void* operator new(decltype(sizeof(0)) n) {
    return rstd::gSystemHeap.alloc(n);
}

void* operator new[](decltype(sizeof(0)) n) {
    return rstd::gSystemHeap.alloc(n);
}

void operator delete(void* p) noexcept {
    return rstd::gSystemHeap.free(p);
}

void operator delete[](void* p) noexcept {
    return rstd::gSystemHeap.free(p);
}

#pragma endregion

#pragma region Heap New/Delete

void* operator new(decltype(sizeof(0)) n, rstd::Heap* heap) {
    RADISH_ASSERT(heap != nullptr);
    return heap->alloc(n);
}

// void* operator new(decltype(sizeof(0)) n, rstd::Heap* heap) noexcept {
//     RADISH_ASSERT(heap != nullptr);
//     return heap->alloc(n);
// }

void* operator new[](decltype(sizeof(0)) n, rstd::Heap* heap) {
    RADISH_ASSERT(heap != nullptr);
    return heap->alloc(n);
}

// void* operator new[](decltype(sizeof(0)) n, rstd::Heap* heap) noexcept {
//     RADISH_ASSERT(heap != nullptr);
//     return heap->alloc(n);
// }

// void operator delete(void* p, rstd::Heap* heap) {
//     RADISH_ASSERT(heap != nullptr);
//     return heap->free(p);
// }

void operator delete(void* p, rstd::Heap* heap) noexcept {
    RADISH_ASSERT(heap != nullptr);
    return heap->free(p);
}

// void operator delete[](void* p, rstd::Heap* heap) {
//     RADISH_ASSERT(heap != nullptr);
//     return heap->free(p);
// }

void operator delete[](void* p, rstd::Heap* heap) noexcept {
    RADISH_ASSERT(heap != nullptr);
    return heap->free(p);
}

#pragma endregion
