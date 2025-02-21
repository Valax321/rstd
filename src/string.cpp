#include "rstd/string.hpp"
#include "rstd/memory.hpp"
#include "rstd/memory/malloc.hpp"

#include <cstring>

namespace rstd {

static SystemHeap gStringHeap{};

namespace str {
usize strlen(const char_type* s) {
    return std::strlen(s);
}

void strcpy(char_type* dst, const char_type* src, usize count) {
    for (usize i = count - 1; i >= 0; --i)
        dst[i] = src[i];
}
}

using namespace str;

String::String() : m_DataSize(1) {
    m_Data = new (&gStringHeap) char[m_DataSize];
}

String::String(const char_type* s) : m_Length(strlen(s)) {
    m_DataSize = m_Length + 1;
    m_Data = new (&gStringHeap) char_type[m_DataSize];
    if (s != nullptr)
        strcpy(m_Data, s, m_Length);
}

String::String(const String& other) 
: m_Length(other.m_Length), m_DataSize(other.m_DataSize) {
    m_Data = new (&gStringHeap) char_type[m_DataSize];
    if (other.m_Data != nullptr)
        strcpy(m_Data, other.m_Data, m_Length);
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
        char_type* newData = new (&gStringHeap) char_type[size];
        strcpy(newData, m_Data, m_Length);
        delete[] m_Data;
        m_Data = newData;
        m_DataSize = size;
    }
}

void String::append(const String& other) {
    ensureSize(length() + other.length());
    ssize startOffset = length() + 1;
    strcpy(m_Data + startOffset, other.m_Data, other.length());
}

void String::append(const char_type* other) {
    if (other == nullptr)
        return;

    auto len = strlen(other);
    if (len == 0)
        return;

    ensureSize(length() + len);
    ssize startOffset = length() + 1;
    strcpy(m_Data + startOffset, other, len);
}

void String::appendN(const char_type* other, usize numChars) {
    if (other == nullptr)
        return;

    if (numChars == 0)
        return;

    ensureSize(length() + numChars);
    ssize startOffset = length() + 1;
    strcpy(m_Data + startOffset, other, numChars);
}

}