#include "short.hpp"

noinline Short short_rshift(Short a, uint8_t count) {
    return a >> count;
}

// op=(Short)
noinline void short_add_set(Short & a, Short b) {
    a += b;
}

noinline void short_sub_set(Short & a, Short b) {
    a -= b;
}

noinline void short_mul_set(Short & a, Short b) {
    a *= b;
}

noinline void short_div_set(Short & a, Short b) {
    a /= b;
}

noinline void short_mod_set(Short & a, Short b) {
    a %= b;
}

// op=(int32_t)
noinline void short_add_set(Short & a, int32_t b) {
    a += b;
}

noinline void short_sub_set(Short & a, int32_t b) {
    a -= b;
}

noinline void short_mul_set(Short & a, int32_t b) {
    a *= b;
}

noinline void short_div_set(Short & a, int32_t b) {
    a /= b;
}

noinline void short_mod_set(Short & a, int32_t b) {
    a %= b;
}

// op(Short, Short)
noinline Short short_add(Short a, Short b) {
    return a + b;
}

noinline Short short_sub(Short a, Short b) {
    return a - b;
}

noinline Short short_mul(Short a, Short b) {
    return a * b;
}

noinline Short short_div(Short a, Short b) {
    return a / b;
}

noinline Short short_mod(Short a, Short b) {
    return a % b;
}

// op(Short, int32_t)
noinline Short short_add(Short a, int32_t b) {
    return a + b;
}

noinline Short short_sub(Short a, int32_t b) {
    return a - b;
}

noinline Short short_mul(Short a, int32_t b) {
    return a * b;
}

noinline Short short_div(Short a, int32_t b) {
    return a / b;
}

noinline Short short_mod(Short a, int32_t b) {
    return a % b;
}

// op(int32_t, Short)
noinline Short short_add(int32_t a, Short b) {
    return a + b;
}

noinline Short short_sub(int32_t a, Short b) {
    return a - b;
}

noinline Short short_mul(int32_t a, Short b) {
    return a * b;
}

noinline Short short_div(int32_t a, Short b) {
    return a / b;
}

noinline Short short_mod(int32_t a, Short b) {
    return a % b;
}


