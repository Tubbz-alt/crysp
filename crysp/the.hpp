#ifndef CRYSP_THE_HPP
#define CRYSP_THE_HPP

#include "is.hpp"

CRYSP_NS_START

template<class E>
E the(T arg) {
    if (!is<E>(arg)) {
        impl::throw_bad_cast();
    }
    return reinterpret_cast<E &>(arg);
}

CRYSP_NS_END

#endif // CRYSP_THE_HPP
