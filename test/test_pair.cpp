#include "crysp/pair.hpp"
#include "crysp/nil.hpp"

CRYSP_NS_USE

CRYSP_NOINLINE T get_t() {
    return t;
}

CRYSP_NOINLINE Nil get_nil() {
    return nil;
}

CRYSP_NOINLINE Pair make_pair(T a, T b) {
    return Pair{a, b};
}

CRYSP_NOINLINE T pair_first(Pair c) {
    return c->first;
}

CRYSP_NOINLINE T pair_second(Pair c) {
    return c->rest;
}
