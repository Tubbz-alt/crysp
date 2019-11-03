#ifndef CRYSP_LIST_HPP
#define CRYSP_LIST_HPP

#include "crysp/cons.hpp"
#include "crysp/nil.hpp"

CRYSP_NS_START

inline constexpr Nil list() noexcept {
    return nil;
}

template<class Arg, class... Args>
Cons list(Arg first, Args... rest) {
    return cons(first, list(rest...));
}

CRYSP_NS_END

#endif // CRYSP_LIST_HPP
