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

#pragma endregion
