#pragma once

#include <rstd/types.hpp>

namespace rstd::hash {

u32 crc32(const u8* data, usize dataLength);

}