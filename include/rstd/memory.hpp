#pragma once

#include <rstd/types.hpp>
#include <rstd/memory/heap.hpp>

#pragma region Override Global New/Delete

void* operator new(decltype(sizeof(0)) n);
void* operator new[](decltype(sizeof(0)) n);

void operator delete(void* p) noexcept;
void operator delete[](void* p) noexcept;

#pragma endregion

#pragma region Heap New/Delete

void* operator new(decltype(sizeof(0)) n, rstd::Heap* heap);
void* operator new[](decltype(sizeof(0)) n, rstd::Heap* heap);

void operator delete(void* p, rstd::Heap* heap) noexcept;
void operator delete[](void* p, rstd::Heap* heap) noexcept;

namespace rstd {

template<typename T, typename... TArgs>
T* heapAlloc(Heap* heap, TArgs... args) {
    return new (heap) T(args...);
}

template<typename T>
T* heapAllocArray(Heap* heap, usize count) {
    return new (heap) T[count];
}

template<typename T>
void heapFree(Heap* heap, T* p) {
    p->~T();
    ::operator delete(p, heap);
}

template<typename T>
void heapFreeArray(Heap* heap, T* p) {
    p->~T();
    ::operator delete(p, heap);
}

}

#pragma endregion
