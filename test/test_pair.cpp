#include "crysp/pair.hpp"

noinline Pair make_pair(T a, T b) {
    return Pair{a, b};
}

noinline T pair_first(Pair c) {
    return c->first;
}

noinline T pair_second(Pair c) {
    return c->second;
}
