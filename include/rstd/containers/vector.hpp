#pragma once

#include <rstd/types.hpp>

namespace rstd {

template<typename T>
struct vector {
    using element_type = T;

private:
    T* m_Data{nullptr};
    usize m_Length{0};
    usize m_Size{0};
};

}