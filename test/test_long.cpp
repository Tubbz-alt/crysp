#include "crysp/long.hpp"

CRYSP_NS_USE

CRYSP_NOINLINE Long long_rshift(Long a, uint8_t count) {
    return a >> count;
}

// op=(Long)
CRYSP_NOINLINE void long_add_set(Long & a, Long b) {
    a += b;
}

CRYSP_NOINLINE void long_sub_set(Long & a, Long b) {
    a -= b;
}

CRYSP_NOINLINE void long_mul_set(Long & a, Long b) {
    a *= b;
}

CRYSP_NOINLINE void long_div_set(Long & a, Long b) {
    a /= b;
}

CRYSP_NOINLINE void long_mod_set(Long & a, Long b) {
    a %= b;
}

// op=(int64_t)
CRYSP_NOINLINE void long_add_set(Long & a, int64_t b) {
    a += b;
}

CRYSP_NOINLINE void long_sub_set(Long & a, int64_t b) {
    a -= b;
}

CRYSP_NOINLINE void long_mul_set(Long & a, int64_t b) {
    a *= b;
}

CRYSP_NOINLINE void long_div_set(Long & a, int64_t b) {
    a /= b;
}

CRYSP_NOINLINE void long_mod_set(Long & a, int64_t b) {
    a %= b;
}

// op(Long, Long)
CRYSP_NOINLINE Long long_add(Long a, Long b) {
    return a + b;
}

CRYSP_NOINLINE Long long_sub(Long a, Long b) {
    return a - b;
}

CRYSP_NOINLINE Long long_mul(Long a, Long b) {
    return a * b;
}

CRYSP_NOINLINE Long long_div(Long a, Long b) {
    return a / b;
}

CRYSP_NOINLINE Long long_mod(Long a, Long b) {
    return a % b;
}

CRYSP_NOINLINE Long long_and(Long a, Long b) {
    return a & b;
}

CRYSP_NOINLINE Long long_or(Long a, Long b) {
    return a | b;
}

CRYSP_NOINLINE Long long_xor(Long a, Long b) {
    return a ^ b;
}

// op(Long, int64_t)
CRYSP_NOINLINE Long long_add(Long a, int64_t b) {
    return a + b;
}

CRYSP_NOINLINE Long long_sub(Long a, int64_t b) {
    return a - b;
}

CRYSP_NOINLINE Long long_mul(Long a, int64_t b) {
    return a * b;
}

CRYSP_NOINLINE Long long_div(Long a, int64_t b) {
    return a / b;
}

CRYSP_NOINLINE Long long_mod(Long a, int64_t b) {
    return a % b;
}

CRYSP_NOINLINE Long long_and(Long a, int64_t b) {
    return a & b;
}

CRYSP_NOINLINE Long long_or(Long a, int64_t b) {
    return a | b;
}

CRYSP_NOINLINE Long long_xor(Long a, int64_t b) {
    return a ^ b;
}

// op(int64_t, Long)
CRYSP_NOINLINE Long long_add(int64_t a, Long b) {
    return a + b;
}

CRYSP_NOINLINE Long long_sub(int64_t a, Long b) {
    return a - b;
}

CRYSP_NOINLINE Long long_mul(int64_t a, Long b) {
    return a * b;
}

CRYSP_NOINLINE Long long_div(int64_t a, Long b) {
    return a / b;
}

CRYSP_NOINLINE Long long_mod(int64_t a, Long b) {
    return a % b;
}

CRYSP_NOINLINE Long long_and(int64_t a, Long b) {
    return a & b;
}

CRYSP_NOINLINE Long long_or(int64_t a, Long b) {
    return a | b;
}

CRYSP_NOINLINE Long long_xor(int64_t a, Long b) {
    return a ^ b;
}

