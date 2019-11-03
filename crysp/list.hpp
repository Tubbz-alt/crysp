#ifndef CRYSP_LIST_HPP
#define CRYSP_LIST_HPP

#include "crysp/nil.hpp"
#include "crysp/pair.hpp"

CRYSP_NS_START

inline constexpr Nil list() noexcept {
    return nil;
}

template<class Arg, class... Args>
Pair list(Arg first, Args... rest) {
    return pair(first, list(rest...));
}

CRYSP_NS_END

#endif // CRYSP_LIST_HPP
