#pragma once

#include <rstd/types.hpp>

namespace rstd::hash {

u64 fnv1a(const u8* data, usize dataLength);

}