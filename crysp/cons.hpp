#ifndef CRYSP_CONS_HPP
#define CRYSP_CONS_HPP

#include "pair.hpp"

CRYSP_NS_START

using Cons = Pair;

inline Cons cons(T first, T rest) {
    return Cons{first, rest};
}       

inline T car(Cons x) {
    return x->first;
}

inline T cdr(Cons x) {
    return x->rest;
}

inline T setf_car(Cons x, T arg) {
    return x->first = arg;
}

inline T setf_cdr(Cons x, T arg) {
    return x->rest = arg;
}

CRYSP_NS_END

#endif // CRYSP_CONS_HPP
