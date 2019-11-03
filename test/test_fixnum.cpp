#include "crysp/fixnum.hpp"

CRYSP_NS_USE

CRYSP_NOINLINE Fixnum fixnum_rshift(Fixnum a, uint8_t count) {
    return a >> count;
}

// op=(Fixnum)
CRYSP_NOINLINE void fixnum_add_ref(Fixnum & a, Fixnum b) {
    a += b;
}

CRYSP_NOINLINE void fixnum_sub_ref(Fixnum & a, Fixnum b) {
    a -= b;
}

CRYSP_NOINLINE void fixnum_mul_ref(Fixnum & a, Fixnum b) {
    a *= b;
}

CRYSP_NOINLINE void fixnum_div_ref(Fixnum & a, Fixnum b) {
    a /= b;
}

CRYSP_NOINLINE void fixnum_mod_ref(Fixnum & a, Fixnum b) {
    a %= b;
}

CRYSP_NOINLINE void fixnum_and_ref(Fixnum & a, Fixnum b) {
    a &= b;
}

CRYSP_NOINLINE void fixnum_or_ref(Fixnum & a, Fixnum b) {
    a |= b;
}

CRYSP_NOINLINE void fixnum_xor_ref(Fixnum & a, Fixnum b) {
    a ^= b;
}

// op=(int64_t)
CRYSP_NOINLINE void fixnum_add_ref(Fixnum & a, int64_t b) {
    a += b;
}

CRYSP_NOINLINE void fixnum_sub_ref(Fixnum & a, int64_t b) {
    a -= b;
}

CRYSP_NOINLINE void fixnum_mul_ref(Fixnum & a, int64_t b) {
    a *= b;
}

CRYSP_NOINLINE void fixnum_div_ref(Fixnum & a, int64_t b) {
    a /= b;
}

CRYSP_NOINLINE void fixnum_mod_ref(Fixnum & a, int64_t b) {
    a %= b;
}

CRYSP_NOINLINE void fixnum_and_ref(Fixnum & a, int64_t b) {
    a &= b;
}

CRYSP_NOINLINE void fixnum_or_ref(Fixnum & a, int64_t b) {
    a |= b;
}

CRYSP_NOINLINE void fixnum_xor_ref(Fixnum & a, int64_t b) {
    a ^= b;
}

// op(Fixnum, Fixnum)
CRYSP_NOINLINE Fixnum fixnum_add(Fixnum a, Fixnum b) {
    return a + b;
}
CRYSP_NOINLINE Fixnum fixnum_add_set(Fixnum a, Fixnum b) {
    return a += b;
}

CRYSP_NOINLINE Fixnum fixnum_sub(Fixnum a, Fixnum b) {
    return a - b;
}
CRYSP_NOINLINE Fixnum fixnum_sub_set(Fixnum a, Fixnum b) {
    return a -= b;
}

CRYSP_NOINLINE Fixnum fixnum_mul(Fixnum a, Fixnum b) {
    return a * b;
}
CRYSP_NOINLINE Fixnum fixnum_mul_set(Fixnum a, Fixnum b) {
    return a *= b;
}

CRYSP_NOINLINE Fixnum fixnum_div(Fixnum a, Fixnum b) {
    return a / b;
}
CRYSP_NOINLINE Fixnum fixnum_div_set(Fixnum a, Fixnum b) {
    return a /= b;
}

CRYSP_NOINLINE Fixnum fixnum_mod(Fixnum a, Fixnum b) {
    return a % b;
}
CRYSP_NOINLINE Fixnum fixnum_mod_set(Fixnum a, Fixnum b) {
    return a %= b;
}

CRYSP_NOINLINE Fixnum fixnum_and(Fixnum a, Fixnum b) {
    return a & b;
}
CRYSP_NOINLINE Fixnum fixnum_and_set(Fixnum a, Fixnum b) {
    return a &= b;
}

CRYSP_NOINLINE Fixnum fixnum_or(Fixnum a, Fixnum b) {
    return a | b;
}
CRYSP_NOINLINE Fixnum fixnum_or_set(Fixnum a, Fixnum b) {
    return a |= b;
}

CRYSP_NOINLINE Fixnum fixnum_xor(Fixnum a, Fixnum b) {
    return a ^ b;
}
CRYSP_NOINLINE Fixnum fixnum_xor_set(Fixnum a, Fixnum b) {
    return a ^= b;
}

// op(Fixnum, int64_t)
CRYSP_NOINLINE Fixnum fixnum_add(Fixnum a, int64_t b) {
    return a + b;
}

CRYSP_NOINLINE Fixnum fixnum_sub(Fixnum a, int64_t b) {
    return a - b;
}

CRYSP_NOINLINE Fixnum fixnum_mul(Fixnum a, int64_t b) {
    return a * b;
}

CRYSP_NOINLINE Fixnum fixnum_div(Fixnum a, int64_t b) {
    return a / b;
}

CRYSP_NOINLINE Fixnum fixnum_mod(Fixnum a, int64_t b) {
    return a % b;
}

CRYSP_NOINLINE Fixnum fixnum_and(Fixnum a, int64_t b) {
    return a & b;
}

CRYSP_NOINLINE Fixnum fixnum_or(Fixnum a, int64_t b) {
    return a | b;
}

CRYSP_NOINLINE Fixnum fixnum_xor(Fixnum a, int64_t b) {
    return a ^ b;
}

// op(int64_t, Fixnum)
CRYSP_NOINLINE Fixnum fixnum_add(int64_t a, Fixnum b) {
    return a + b;
}

CRYSP_NOINLINE Fixnum fixnum_sub(int64_t a, Fixnum b) {
    return a - b;
}

CRYSP_NOINLINE Fixnum fixnum_mul(int64_t a, Fixnum b) {
    return a * b;
}

CRYSP_NOINLINE Fixnum fixnum_div(int64_t a, Fixnum b) {
    return a / b;
}

CRYSP_NOINLINE Fixnum fixnum_mod(int64_t a, Fixnum b) {
    return a % b;
}

CRYSP_NOINLINE Fixnum fixnum_and(int64_t a, Fixnum b) {
    return a & b;
}

CRYSP_NOINLINE Fixnum fixnum_or(int64_t a, Fixnum b) {
    return a | b;
}

CRYSP_NOINLINE Fixnum fixnum_xor(int64_t a, Fixnum b) {
    return a ^ b;
}

