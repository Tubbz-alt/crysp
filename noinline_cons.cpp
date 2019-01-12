#include "cons.hpp"

noinline Cons make_cons(T a, T b) {
    return Cons{a, b};
}

noinline T cons_first(Cons c) {
    return c->first;
}

noinline T cons_rest(Cons c) {
    return c->rest;
}
