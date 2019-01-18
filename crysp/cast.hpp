#ifndef CRYSP_CAST_HPP
#define CRYSP_CAST_HPP

#include "crysp/t.hpp"

template<class To>
inline bool is(T arg) {
    return To::typecheck(arg.bits);
}

template<class To>
inline bool is(To) {
    return true;
}

template<class To>
/*noinline*/ To cast(T arg) {
    if (!is<To>(arg)) {
        impl::throw_bad_cast();
    }
    return reinterpret_cast<To &>(arg);
}

#endif // CRYSP_CAST_HPP
