#ifndef CRYSP_IS_HPP
#define CRYSP_IS_HPP

#include "t.hpp"

CRYSP_NS_START

template<class E>
inline bool is(T arg) {
    return E::typecheck(arg.bits);
}

template<class E>
inline bool is(E) {
    return true;
}

template<class E>
bool is(T arg, E *ret) {
    if (!is<E>(arg)) {
        return false;
    }
    *ret = reinterpret_cast<E &>(arg);
    return true;
}


CRYSP_NS_END

#endif // CRYSP_IS_HPP
