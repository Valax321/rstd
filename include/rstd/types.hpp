#pragma once

#include <cstddef>
#include <cstdint>

namespace rstd
{
    using u8 = uint8_t;
    using s8 = int8_t;

    using u16 = uint16_t;
    using s16 = int16_t;

    using u32 = uint32_t;
    using s32 = int32_t;

    using u64 = uint64_t;
    using s64 = int64_t;

    using f32 = float;
    using f64 = double;

    using usize = size_t;
    using ssize = ptrdiff_t;

    constexpr auto U8_MAX = UINT8_MAX;
    constexpr auto S8_MIN = INT8_MIN;
    constexpr auto S8_MAX = INT8_MAX;

    constexpr auto U16_MAX = UINT16_MAX;
    constexpr auto S16_MIN = INT16_MIN;
    constexpr auto S16_MAX = INT16_MAX;

    constexpr auto U32_MAX = UINT32_MAX;
    constexpr auto S32_MIN = INT32_MIN;
    constexpr auto S32_MAX = INT32_MAX;

    constexpr auto U64_MAX = UINT64_MAX;
    constexpr auto S64_MIN = INT64_MIN;
    constexpr auto S64_MAX = INT64_MAX;

    constexpr auto USIZE_MAX = SIZE_MAX;
    constexpr auto SSIZE_MIN = PTRDIFF_MIN;
    constexpr auto SSIZE_MAX = PTRDIFF_MAX;
}
