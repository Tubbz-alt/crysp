#ifndef CRYSP_FIXNUM_HPP
#define CRYSP_FIXNUM_HPP

#include "long.hpp"

CRYSP_NS_START

using Fixnum = Long;

constexpr const Long fixnum_max = long_max;
constexpr const Long fixnum_min = long_min;

CRYSP_NS_END

#endif // CRYSP_FIXNUM_HPP
