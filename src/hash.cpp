#include "rstd/hash/fnv1a.hpp"

namespace rstd::hash {

constexpr u64 FNV_OFFSET_BASIS = 0xcbf29ce484222325;
constexpr u64 FNV_PRIME = 0x100000001b3;

u64 fnv1a(const u8* data, usize dataLength) {
    u64 hash = FNV_OFFSET_BASIS;
    for (usize i = 0; i < dataLength; ++i) {
        hash ^= (data[i]);
        hash *= FNV_PRIME;
    }

    return hash;
}

u32 crc32(const u8* data, usize dataLength) {
    return 0;
}

}