#pragma once

#include <rstd/types.hpp>
#include <rstd/assert.hpp>

namespace rstd {

using char_type = char;
constexpr static auto CHAR_SIZE = sizeof(char_type);

namespace str {
usize strlen(const char_type* s);
void strcpy(char_type* dst, const char_type* src, usize count);
}

template<usize Count>
struct FixedString;

struct String {
    String();
    String(const char_type* s);
    String(const String& other);
    String(const String&& other) noexcept;

    virtual ~String();

    void ensureSize(usize size);

    void append(const String& other);

    void append(const char_type* other);
    void appendN(const char_type* other, usize numChars);

    template<usize Count>
    void append(const FixedString<Count>& other) {
        appendN(other.cstr(), other.length());
    }

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

private:
    char* m_Data{nullptr};
    usize m_Length{0};
    usize m_DataSize{0};
};

template<usize Count>
struct FixedString
{
    constexpr static auto MAX_LENGTH = Count - 1;

    constexpr FixedString() = default;
    FixedString(const char_type* s) : m_Length(getClampedLength(str::strlen(s))) {
        if (s != nullptr)
            str::strcpy(m_Data, s, m_Length);
    }

    FixedString(const String& other) : m_Length(getClampedLength(other.length())) {
        str::strcpy(m_Data, other.cstr(), m_Length);
    }

    virtual ~FixedString() = default;

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

private:
    [[nodiscard]]
    constexpr static usize getClampedLength(usize length) {
        return length > MAX_LENGTH ? MAX_LENGTH : length;
    }

    char_type m_Data[Count];
    usize m_Length{0};
};

#pragma region Append Operators

void operator +=(String& s, const String& other) {
    s.append(other);        
}

void operator +=(String& s, const char_type* other) {
    s.append(other);
}

template<usize Count>
void operator +=(String& s, const FixedString<Count>& other) {
    s.append<Count>(other);
}

String operator +(String lhs, const String& rhs) {
    lhs.append(rhs);
    return lhs;
}

String operator +(String lhs, const char_type* rhs) {
    lhs.append(rhs);
    return lhs;
}

template<usize Count>
String operator +(String lhs, const FixedString<Count>& rhs) {
    lhs.append<Count>(rhs);
    return lhs;
}

template<usize Count>
void operator +=(FixedString<Count>& s, const String& other) {
    s.append(other);
}

template<usize Count>
void operator +=(FixedString<Count>& s, const char_type* other) {
    s.append<Count>(other);
}

template<usize Count>
void operator +=(FixedString<Count>& s, const FixedString<Count>& other) {
    s.append<Count>(other);
}

#pragma endregion

}