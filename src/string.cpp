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

}

String::String() : m_DataSize(1) {
    m_Data = new char[m_DataSize];
}

String::String(const char_type* s) : m_Length(strlen(s)) {
    m_DataSize = m_Length + 1;
    m_Data = new char_type[m_DataSize];
    if (s != nullptr)
        str::strcpy(m_Data, s, m_Length);
}

String::String(const String& other) 
: m_Length(other.m_Length), m_DataSize(other.m_DataSize) {
    m_Data = new char_type[m_DataSize];
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
        str::strcpy(newData, m_Data, m_Length);
        delete[] m_Data;
        m_Data = newData;
        m_DataSize = size;
    }
}

void String::append(const String& other) {
    ensureSize((length() + other.length()) + 1);
    ssize startOffset = length();
    str::strcpy(m_Data + startOffset, other.m_Data, other.length());
}

void String::append(const char_type* other) {
    if (other == nullptr)
        return;

    auto len = strlen(other);
    if (len == 0)
        return;

    ensureSize((length() + len) + 1);
    ssize startOffset = length();
    str::strcpy(m_Data + startOffset, other, len);
}

void String::appendN(const char_type* other, usize numChars) {
    if (other == nullptr)
        return;

    if (numChars == 0)
        return;

    ensureSize((length() + numChars) + 1);
    ssize startOffset = length();
    str::strcpy(m_Data + startOffset, other, numChars);
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

}