#pragma once

#include <rstd/types.hpp>
#include <rstd/assert.hpp>
#include <rstd/containers/iterator.hpp>

namespace rstd {

using char_type = char;
constexpr static auto CHAR_SIZE = sizeof(char_type);

namespace str {
usize strlen(const char_type* s);
void strcpy(char_type* dst, const char_type* src, usize count);
void zero(char_type* p, usize sz);
int strcmp(const char_type* lhs, const char_type* rhs);
}

template<usize Count>
struct FixedString;

struct String {
    using Iterator = rstd::ArrayIterator<char_type>;
    using ConstIterator = rstd::ConstArrayIterator<char_type>;

    String();
    String(const char_type* s);
    String(const String& other);
    String(const String&& other) noexcept;

    virtual ~String();

    void ensureSize(usize size);

    void append(char_type c);
    void append(const String& other);
    void append(const char_type* other);
    void appendN(const char_type* other, usize numChars);

    template<usize Count>
    void append(const FixedString<Count>& other) {
        appendN(other.cstr(), other.length());
    }

    void appendFast(const char_type* other, usize numChars);

    void copyTo(String& other) const;
    void copyTo(char_type* other, usize count) const;

    template<usize Count>
    void copyTo(FixedString<Count>& other) const {
        copyTo(other.cstr(), other.length());
    }

    String substring(usize start, usize count) const;
    String substring(ConstIterator start, ConstIterator end) const;

    /**
     * NOTE: this is the length WITHOUT the null terminator.
     */
    [[nodiscard]]
    usize length() const { return m_Length; }

    /**
     * NOTE: this is the length WITH the null terminator.
     */
    [[nodiscard]]
    usize size() const { return m_DataSize; }

    [[nodiscard]]
    char_type* cstr() { return m_Data; }

    [[nodiscard]]
    const char_type* cstr() const { return m_Data; }

    [[nodiscard]]
    bool isEmpty() const { return m_Length == 0; }

    Iterator begin() { return Iterator(m_Data, m_Data); }
    ConstIterator begin() const { return ConstIterator(m_Data, m_Data); }
    Iterator end() { return Iterator(m_Data, m_Data + m_Length); }
    ConstIterator end() const { return ConstIterator(m_Data, m_Data + m_Length); }

    Iterator at(usize position);
    ConstIterator at(usize position) const;

    char_type& operator [](usize i) {
        RADISH_ASSERT(i < m_Length);
        return m_Data[i];
    }

    char_type operator [](usize i) const {
        RADISH_ASSERT(i < m_Length);
        return m_Data[i];
    }

private:
    char* m_Data{nullptr};
    usize m_Length{0};
    usize m_DataSize{0};
};

template<usize Count>
struct FixedString
{
    constexpr static auto MAX_LENGTH = Count - 1;
    // Re-use the dynamic string iterators for compatibility
    using Iterator = rstd::String::Iterator;
    using ConstIterator = rstd::String::ConstIterator;

    constexpr FixedString() = default;
    FixedString(const char_type* s) : m_Length(getClampedLength(str::strlen(s))) {
        if (s != nullptr)
            str::strcpy(m_Data, s, m_Length);
    }

    FixedString(const String& other) : m_Length(getClampedLength(other.length())) {
        str::strcpy(m_Data, other.cstr(), m_Length);
    }

    virtual ~FixedString() = default;

    usize append(char_type c) {
        if (length() + 1 > MAX_LENGTH)
            return 0;

        m_Data[m_Length] = c;
        m_Length++;
    }

    usize append(const String& other) {
        auto actualLength = other.length();
        if ((actualLength + length()) > MAX_LENGTH)
            actualLength = (actualLength + length()) - MAX_LENGTH;

        m_Length += actualLength;
        str::strcpy(m_Data, other.cstr(), actualLength);
        return actualLength;
    }

    usize append(const char_type* other) {
        auto actualLength = str::strlen(other);
        if ((actualLength + length()) > MAX_LENGTH)
            actualLength = (actualLength + length()) - MAX_LENGTH;

        m_Length += actualLength;
        str::strcpy(m_Data, other, actualLength);
        return actualLength;
    }

    usize append(const FixedString<Count>& other) {
        auto actualLength = other.length();
        if ((actualLength + length()) > MAX_LENGTH)
            actualLength = (actualLength + length()) - MAX_LENGTH;

        m_Length += actualLength;
        str::strcpy(m_Data, other.cstr(), actualLength);
        return actualLength;
    }

    [[nodiscard]]
    usize length() const { return m_Length; }

    [[nodiscard]]
    constexpr usize size() const { return Count; }

    [[nodiscard]]
    char_type* cstr() { return m_Data; }

    [[nodiscard]]
    const char_type* cstr() const { return m_Data; }

    bool isEmpty() const { return m_Length == 0; }

    Iterator begin() { return Iterator(m_Data, m_Data); }
    ConstIterator begin() const { return ConstIterator(m_Data, m_Data); }
    Iterator end() { return Iterator(m_Data, m_Data + m_Length); }
    ConstIterator end() const { return ConstIterator(m_Data, m_Data + m_Length); }

    Iterator at(usize position) {
        RADISH_ASSERT(position < m_Length);
        return Iterator(m_Data, m_Data + position);
    }

    ConstIterator at(usize position) const {
        RADISH_ASSERT(position < m_Length);
        return ConstIterator(m_Data, m_Data + position);
    }

    char_type& operator [](usize i) {
        RADISH_ASSERT(i < m_Length);
        return m_Data[i];
    }

    char_type operator [](usize i) const {
        RADISH_ASSERT(i < m_Length);
        return m_Data[i];
    }

private:
    [[nodiscard]]
    constexpr static usize getClampedLength(usize length) {
        return length > MAX_LENGTH ? MAX_LENGTH : length;
    }

    char_type m_Data[Count]{0};
    usize m_Length{0};
};

#pragma region Append Operators

void operator +=(String& s, const String& other);
void operator +=(String& s, const char_type* other);

template<usize Count>
inline void operator +=(String& s, const FixedString<Count>& other) {
    s.append<Count>(other);
}

String operator +(String lhs, const String& rhs);
String operator +(String lhs, const char_type* rhs);

template<usize Count>
inline String operator +(String lhs, const FixedString<Count>& rhs) {
    lhs.append<Count>(rhs);
    return lhs;
}

template<usize Count>
inline void operator +=(FixedString<Count>& s, const String& other) {
    s.append(other);
}

template<usize Count>
inline void operator +=(FixedString<Count>& s, const char_type* other) {
    s.append<Count>(other);
}

template<usize Count>
inline void operator +=(FixedString<Count>& s, const FixedString<Count>& other) {
    s.append<Count>(other);
}

#pragma endregion

#pragma region Equality Operators

bool operator ==(const String& lhs, const String& rhs);
bool operator !=(const String& lhs, const String& rhs);

// These allow supporting all combos of dynamic, fixed and c strings for comparison.

template<typename LHS, typename RHS>
bool operator ==(const LHS& lhs, const RHS& rhs) {
    return str::strcmp(lhs.cstr(), rhs.cstr()) == 0;
}

template<typename LHS, typename RHS>
bool operator ==(const LHS& lhs, const RHS* rhs) {
    return str::strcmp(lhs.cstr(), rhs) == 0;
}

template<typename LHS, typename RHS>
bool operator ==(const LHS* lhs, const RHS& rhs) {
    return str::strcmp(lhs, rhs.cstr()) == 0;
}

template<typename LHS, typename RHS>
bool operator !=(const LHS& lhs, const RHS& rhs) {
    return !(lhs == rhs);
}

#pragma endregion

}