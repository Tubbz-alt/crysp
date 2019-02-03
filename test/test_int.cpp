#include "crysp/int.hpp"

CRYSP_NS_USE

CRYSP_NOINLINE Int int_rshift(Int a, uint8_t count) {
    return a >> count;
}

// op=(Int)
CRYSP_NOINLINE void int_add_ref(Int & a, Int b) {
    a += b;
}

CRYSP_NOINLINE void int_sub_ref(Int & a, Int b) {
    a -= b;
}

CRYSP_NOINLINE void int_mul_ref(Int & a, Int b) {
    a *= b;
}

CRYSP_NOINLINE void int_div_ref(Int & a, Int b) {
    a /= b;
}

CRYSP_NOINLINE void int_mod_ref(Int & a, Int b) {
    a %= b;
}

CRYSP_NOINLINE void int_and_ref(Int & a, Int b) {
    a &= b;
}

CRYSP_NOINLINE void int_or_ref(Int & a, Int b) {
    a |= b;
}

CRYSP_NOINLINE void int_xor_ref(Int & a, Int b) {
    a ^= b;
}

// op=(int32_t)
CRYSP_NOINLINE void int_add_ref(Int & a, int32_t b) {
    a += b;
}

CRYSP_NOINLINE void int_sub_ref(Int & a, int32_t b) {
    a -= b;
}

CRYSP_NOINLINE void int_mul_ref(Int & a, int32_t b) {
    a *= b;
}

CRYSP_NOINLINE void int_div_ref(Int & a, int32_t b) {
    a /= b;
}

CRYSP_NOINLINE void int_mod_ref(Int & a, int32_t b) {
    a %= b;
}

CRYSP_NOINLINE void int_and_ref(Int & a, int32_t b) {
    a &= b;
}

CRYSP_NOINLINE void int_or_ref(Int & a, int32_t b) {
    a |= b;
}

CRYSP_NOINLINE void int_xor_ref(Int & a, int32_t b) {
    a ^= b;
}

// op(Int, Int)
CRYSP_NOINLINE Int int_add(Int a, Int b) {
    return a + b;
}

CRYSP_NOINLINE Int int_sub(Int a, Int b) {
    return a - b;
}

CRYSP_NOINLINE Int int_mul(Int a, Int b) {
    return a * b;
}

CRYSP_NOINLINE Int int_div(Int a, Int b) {
    return a / b;
}

CRYSP_NOINLINE Int int_mod(Int a, Int b) {
    return a % b;
}

CRYSP_NOINLINE Int int_and(Int a, Int b) {
    return a & b;
}

CRYSP_NOINLINE Int int_or(Int a, Int b) {
    return a | b;
}

CRYSP_NOINLINE Int int_xor(Int a, Int b) {
    return a ^ b;
}

// op(Int, int32_t)
CRYSP_NOINLINE Int int_add(Int a, int32_t b) {
    return a + b;
}

CRYSP_NOINLINE Int int_sub(Int a, int32_t b) {
    return a - b;
}

CRYSP_NOINLINE Int int_mul(Int a, int32_t b) {
    return a * b;
}

CRYSP_NOINLINE Int int_div(Int a, int32_t b) {
    return a / b;
}

CRYSP_NOINLINE Int int_mod(Int a, int32_t b) {
    return a % b;
}

CRYSP_NOINLINE Int int_and(Int a, int32_t b) {
    return a & b;
}

CRYSP_NOINLINE Int int_or(Int a, int32_t b) {
    return a | b;
}

CRYSP_NOINLINE Int int_xor(Int a, int32_t b) {
    return a ^ b;
}

// op(int32_t, Int)
CRYSP_NOINLINE Int int_add(int32_t a, Int b) {
    return a + b;
}

CRYSP_NOINLINE Int int_sub(int32_t a, Int b) {
    return a - b;
}

CRYSP_NOINLINE Int int_mul(int32_t a, Int b) {
    return a * b;
}

CRYSP_NOINLINE Int int_div(int32_t a, Int b) {
    return a / b;
}

CRYSP_NOINLINE Int int_mod(int32_t a, Int b) {
    return a % b;
}

CRYSP_NOINLINE Int int_and(int32_t a, Int b) {
    return a & b;
}

CRYSP_NOINLINE Int int_or(int32_t a, Int b) {
    return a | b;
}

CRYSP_NOINLINE Int int_xor(int32_t a, Int b) {
    return a ^ b;
}

