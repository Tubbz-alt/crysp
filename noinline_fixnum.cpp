#include "fixnum.hpp"

noinline Fixnum fixnum_rshift(Fixnum a, uint8_t count) {
    return a >> count;
}

// op=(Fixnum)
noinline void fixnum_add_set(Fixnum & a, Fixnum b) {
    a += b;
}

noinline void fixnum_sub_set(Fixnum & a, Fixnum b) {
    a -= b;
}

noinline void fixnum_mul_set(Fixnum & a, Fixnum b) {
    a *= b;
}

noinline void fixnum_div_set(Fixnum & a, Fixnum b) {
    a /= b;
}

noinline void fixnum_mod_set(Fixnum & a, Fixnum b) {
    a %= b;
}

// op=(int64_t)
noinline void fixnum_add_set(Fixnum & a, int64_t b) {
    a += b;
}

noinline void fixnum_sub_set(Fixnum & a, int64_t b) {
    a -= b;
}

noinline void fixnum_mul_set(Fixnum & a, int64_t b) {
    a *= b;
}

noinline void fixnum_div_set(Fixnum & a, int64_t b) {
    a /= b;
}

noinline void fixnum_mod_set(Fixnum & a, int64_t b) {
    a %= b;
}

// op(Fixnum, Fixnum)
noinline Fixnum fixnum_add(Fixnum a, Fixnum b) {
    return a + b;
}

noinline Fixnum fixnum_sub(Fixnum a, Fixnum b) {
    return a - b;
}

noinline Fixnum fixnum_mul(Fixnum a, Fixnum b) {
    return a * b;
}

noinline Fixnum fixnum_div(Fixnum a, Fixnum b) {
    return a / b;
}

noinline Fixnum fixnum_mod(Fixnum a, Fixnum b) {
    return a % b;
}

// op(Fixnum, int64_t)
noinline Fixnum fixnum_add(Fixnum a, int64_t b) {
    return a + b;
}

noinline Fixnum fixnum_sub(Fixnum a, int64_t b) {
    return a - b;
}

noinline Fixnum fixnum_mul(Fixnum a, int64_t b) {
    return a * b;
}

noinline Fixnum fixnum_div(Fixnum a, int64_t b) {
    return a / b;
}

noinline Fixnum fixnum_mod(Fixnum a, int64_t b) {
    return a % b;
}

// op(int64_t, Fixnum)
noinline Fixnum fixnum_add(int64_t a, Fixnum b) {
    return a + b;
}

noinline Fixnum fixnum_sub(int64_t a, Fixnum b) {
    return a - b;
}

noinline Fixnum fixnum_mul(int64_t a, Fixnum b) {
    return a * b;
}

noinline Fixnum fixnum_div(int64_t a, Fixnum b) {
    return a / b;
}

noinline Fixnum fixnum_mod(int64_t a, Fixnum b) {
    return a % b;
}


