#include "fixint.hpp"

noinline Fixint fixint_rshift(Fixint a, uint8_t count) {
    return a >> count;
}

// op=(Fixint)
noinline void fixint_add_set(Fixint & a, Fixint b) {
    a += b;
}

noinline void fixint_sub_set(Fixint & a, Fixint b) {
    a -= b;
}

noinline void fixint_mul_set(Fixint & a, Fixint b) {
    a *= b;
}

noinline void fixint_div_set(Fixint & a, Fixint b) {
    a /= b;
}

noinline void fixint_mod_set(Fixint & a, Fixint b) {
    a %= b;
}

// op=(int64_t)
noinline void fixint_add_set(Fixint & a, int64_t b) {
    a += b;
}

noinline void fixint_sub_set(Fixint & a, int64_t b) {
    a -= b;
}

noinline void fixint_mul_set(Fixint & a, int64_t b) {
    a *= b;
}

noinline void fixint_div_set(Fixint & a, int64_t b) {
    a /= b;
}

noinline void fixint_mod_set(Fixint & a, int64_t b) {
    a %= b;
}

// op(Fixint, Fixint)
noinline Fixint fixint_add(Fixint a, Fixint b) {
    return a + b;
}

noinline Fixint fixint_sub(Fixint a, Fixint b) {
    return a - b;
}

noinline Fixint fixint_mul(Fixint a, Fixint b) {
    return a * b;
}

noinline Fixint fixint_div(Fixint a, Fixint b) {
    return a / b;
}

noinline Fixint fixint_mod(Fixint a, Fixint b) {
    return a % b;
}

// op(Fixint, int64_t)
noinline Fixint fixint_add(Fixint a, int64_t b) {
    return a + b;
}

noinline Fixint fixint_sub(Fixint a, int64_t b) {
    return a - b;
}

noinline Fixint fixint_mul(Fixint a, int64_t b) {
    return a * b;
}

noinline Fixint fixint_div(Fixint a, int64_t b) {
    return a / b;
}

noinline Fixint fixint_mod(Fixint a, int64_t b) {
    return a % b;
}

// op(int64_t, Fixint)
noinline Fixint fixint_add(int64_t a, Fixint b) {
    return a + b;
}

noinline Fixint fixint_sub(int64_t a, Fixint b) {
    return a - b;
}

noinline Fixint fixint_mul(int64_t a, Fixint b) {
    return a * b;
}

noinline Fixint fixint_div(int64_t a, Fixint b) {
    return a / b;
}

noinline Fixint fixint_mod(int64_t a, Fixint b) {
    return a % b;
}


