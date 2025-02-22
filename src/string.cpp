#include "rstd/string.hpp"
#include "rstd/memory.hpp"
#include "rstd/memory/malloc.hpp"

#include <cstring>

namespace rstd {

// TODO: Need to work out a better use pattern for heaps before we use this
//static SystemHeap gStringHeap{};

namespace str {

usize strlen(const char_type* s) {
    return std::strlen(s);
}

void strcpy(char_type* dst, const char_type* src, usize count) {
    for (usize i = 0; i < count; ++i)
        dst[i] = src[i];
}

void zero(char_type* p, usize sz) {
    std::memset(p, 0, sz);
}

int strcmp(const char_type* lhs, const char_type* rhs) {
    return std::strcmp(lhs, rhs);
}

}

String::String() : m_DataSize(1) {
    m_Data = new char[m_DataSize];
    str::zero(m_Data, m_DataSize);
}

String::String(const char_type* s) : m_Length(str::strlen(s)) {
    m_DataSize = m_Length + 1;
    m_Data = new char_type[m_DataSize];
    str::zero(m_Data, m_DataSize);
    if (s != nullptr)
        str::strcpy(m_Data, s, m_Length);
}

String::String(const String& other) 
: m_Length(other.m_Length), m_DataSize(other.m_DataSize) {
    m_Data = new char_type[m_DataSize];
    str::zero(m_Data, m_DataSize);
    if (other.m_Data != nullptr)
        str::strcpy(m_Data, other.m_Data, m_Length);
}

String::String(const String&& other) noexcept
: m_Length(other.m_Length), m_DataSize(other.m_DataSize) {
    m_Data = other.m_Data;
}

String::~String() {
    delete[] m_Data;
    m_Data = nullptr;
}

void String::ensureSize(usize size) {
    if (m_DataSize < size) {
        char_type* newData = new char_type[size];
        str::zero(newData, size);
        str::strcpy(newData, m_Data, m_Length);
        delete[] m_Data;
        m_Data = newData;
        m_DataSize = size;
    }
}

void String::append(char_type c) {
    appendN(&c, 1);
}

void String::append(const String& other) {
    ensureSize((length() + other.length()) + 1);
    ssize startOffset = length();
    str::strcpy(m_Data + startOffset, other.m_Data, other.length());
    m_Length += other.length();
}

void String::append(const char_type* other) {
    if (other == nullptr)
        return;

    auto len = str::strlen(other);
    if (len == 0)
        return;

    ensureSize((length() + len) + 1);
    ssize startOffset = length();
    str::strcpy(m_Data + startOffset, other, len);
    m_Length += len;
}

void String::appendN(const char_type* other, usize numChars) {
    if (other == nullptr)
        return;

    if (numChars == 0)
        return;

    ensureSize((length() + numChars) + 1);
    ssize startOffset = length();
    str::strcpy(m_Data + startOffset, other, numChars);
    m_Length += numChars;
}

void String::appendFast(const char_type* other, usize numChars) {
    ssize startOffset = length();
    str::strcpy(m_Data + startOffset, other, numChars);
    m_Length += numChars;
}

void String::copyTo(String& other) const {
    other.ensureSize(length() + 1);
    str::strcpy(other.cstr(), cstr(), length());
}

void String::copyTo(char_type* other, usize count) const {
    RADISH_ASSERT(other != nullptr);
    auto copyChars = length();
    if (copyChars > count)
        copyChars = count;
    str::strcpy(other, cstr(), copyChars);
}

String String::substring(usize start, usize count) const {
    RADISH_ASSERT(start + count < length());
    String r{};
    r.ensureSize(count + 1);
    str::strcpy(r.cstr(), cstr(), count);
    return r;
}

String String::substring(ConstIterator start, ConstIterator end) const {
    RADISH_ASSERT(start >= this->begin());
    RADISH_ASSERT(end <= this->end());

    String r{};
    r.ensureSize((end - start) + 1);
    for (auto i = start; i < end; ++i)
        r.appendFast(&(*i), 1);
    return r;
}

String::Iterator String::at(usize position) {
    RADISH_ASSERT(position < length());
    return Iterator(m_Data, m_Data + position);
}

String::ConstIterator String::at(usize position) const {
    RADISH_ASSERT(position < length());
    return ConstIterator(m_Data, m_Data + position);
}

void operator +=(String& s, const String& other) {
    s.append(other);        
}

void operator +=(String& s, const char_type* other) {
    s.append(other);
}

String operator +(String lhs, const String& rhs) {
    lhs.append(rhs);
    return lhs;
}

String operator +(String lhs, const char_type* rhs) {
    lhs.append(rhs);
    return lhs;
}

bool operator ==(const String& lhs, const String& rhs) {
    return str::strcmp(lhs.cstr(), rhs.cstr()) == 0;
}

bool operator !=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

}