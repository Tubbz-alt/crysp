#include "crysp/int.hpp"

CRYSP_NS_USE

CRYSP_NOINLINE Int int_rshift(Int a, uint8_t count) {
    return a >> count;
}

// op=(Int)
CRYSP_NOINLINE void int_add_set(Int & a, Int b) {
    a += b;
}

CRYSP_NOINLINE void int_sub_set(Int & a, Int b) {
    a -= b;
}

CRYSP_NOINLINE void int_mul_set(Int & a, Int b) {
    a *= b;
}

CRYSP_NOINLINE void int_div_set(Int & a, Int b) {
    a /= b;
}

CRYSP_NOINLINE void int_mod_set(Int & a, Int b) {
    a %= b;
}

// op=(int64_t)
CRYSP_NOINLINE void int_add_set(Int & a, int64_t b) {
    a += b;
}

CRYSP_NOINLINE void int_sub_set(Int & a, int64_t b) {
    a -= b;
}

CRYSP_NOINLINE void int_mul_set(Int & a, int64_t b) {
    a *= b;
}

CRYSP_NOINLINE void int_div_set(Int & a, int64_t b) {
    a /= b;
}

CRYSP_NOINLINE void int_mod_set(Int & a, int64_t b) {
    a %= b;
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

// op(Int, int64_t)
CRYSP_NOINLINE Int int_add(Int a, int64_t b) {
    return a + b;
}

CRYSP_NOINLINE Int int_sub(Int a, int64_t b) {
    return a - b;
}

CRYSP_NOINLINE Int int_mul(Int a, int64_t b) {
    return a * b;
}

CRYSP_NOINLINE Int int_div(Int a, int64_t b) {
    return a / b;
}

CRYSP_NOINLINE Int int_mod(Int a, int64_t b) {
    return a % b;
}

CRYSP_NOINLINE Int int_and(Int a, int64_t b) {
    return a & b;
}

CRYSP_NOINLINE Int int_or(Int a, int64_t b) {
    return a | b;
}

CRYSP_NOINLINE Int int_xor(Int a, int64_t b) {
    return a ^ b;
}

// op(int64_t, Int)
CRYSP_NOINLINE Int int_add(int64_t a, Int b) {
    return a + b;
}

CRYSP_NOINLINE Int int_sub(int64_t a, Int b) {
    return a - b;
}

CRYSP_NOINLINE Int int_mul(int64_t a, Int b) {
    return a * b;
}

CRYSP_NOINLINE Int int_div(int64_t a, Int b) {
    return a / b;
}

CRYSP_NOINLINE Int int_mod(int64_t a, Int b) {
    return a % b;
}

CRYSP_NOINLINE Int int_and(int64_t a, Int b) {
    return a & b;
}

CRYSP_NOINLINE Int int_or(int64_t a, Int b) {
    return a | b;
}

CRYSP_NOINLINE Int int_xor(int64_t a, Int b) {
    return a ^ b;
}

