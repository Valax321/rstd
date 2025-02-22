#pragma once

#include <rstd/types.hpp>
#include <rstd/assert.hpp>

namespace rstd {

template<typename T>
struct ConstArrayIterator final {
    using element_type = T;

    ConstArrayIterator(const T* start, T* ptr) : m_Ptr(ptr), m_Start(start)
    {
        RADISH_ASSERT(m_Ptr != nullptr);
    }

    const T& operator *() const {
        return *m_Ptr;
    }

    ConstArrayIterator& operator ++() {
        m_Ptr++;
        return *this;
    }

    ConstArrayIterator& operator --() {
        m_Ptr--;
        return *this;
    }

    bool operator ==(const ConstArrayIterator& other) const {
        return m_Ptr == other.m_Ptr;
    }

    bool operator !=(const ConstArrayIterator& other) const {
        return !(*this == other);
    }

    bool operator >(const ConstArrayIterator& other) const {
        return m_Ptr > other.m_Ptr;
    }

    bool operator >=(const ConstArrayIterator& other) const {
        return m_Ptr >= other.m_Ptr;
    }

    bool operator <(const ConstArrayIterator& other) const {
        return m_Ptr < other.m_Ptr;
    }

    bool operator <=(const ConstArrayIterator& other) const {
        return m_Ptr <= other.m_Ptr;
    }

    ssize operator -(const ConstArrayIterator& other) const {
        return m_Ptr - other.m_Ptr;
    }

    operator const T&() const {
        return *(*this);
    }

    ssize index() const { return m_Ptr - m_Start; }

private:
    T* m_Ptr{nullptr};
    const T* m_Start{nullptr};
};

template<typename T>
struct ArrayIterator final {
    using element_type = T;

    ArrayIterator(const T* start, T* ptr) : m_Ptr(ptr), m_Start(start)
    {
        RADISH_ASSERT(m_Ptr != nullptr);
    }

    T& operator *() {
        return *m_Ptr;
    }

    const T& operator *() const {
        return *m_Ptr;
    }

    ArrayIterator& operator ++() {
        m_Ptr++;
        return *this;
    }

    ArrayIterator& operator --() {
        m_Ptr--;
        return *this;
    }

    bool operator ==(const ArrayIterator& other) const {
        return m_Ptr == other.m_Ptr;
    }

    bool operator !=(const ArrayIterator& other) const {
        return !(*this == other);
    }

    bool operator >(const ArrayIterator& other) const {
        return m_Ptr > other.m_Ptr;
    }

    bool operator >=(const ArrayIterator& other) const {
        return m_Ptr >= other.m_Ptr;
    }

    bool operator <(const ArrayIterator& other) const {
        return m_Ptr < other.m_Ptr;
    }

    bool operator <=(const ArrayIterator& other) const {
        return m_Ptr <= other.m_Ptr;
    }

    ssize operator -(const ArrayIterator& other) const {
        return m_Ptr - other.m_Ptr;
    }

    operator T&() {
        return *(*this);
    }

    operator const T&() const {
        return *(*this);
    }

    operator ConstArrayIterator<T>() const {
        return ConstArrayIterator<T>(m_Start, m_Ptr);
    }

    ssize index() const { return m_Ptr - m_Start; }

private:
    T* m_Ptr{nullptr};
    const T* m_Start{nullptr};
};

}