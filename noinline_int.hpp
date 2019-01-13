#include "int.hpp"

noinline Int int_rshift(Int a, uint8_t count) {
    return a >> count;
}

// op=(Int)
noinline void int_add_set(Int & a, Int b) {
    a += b;
}

noinline void int_sub_set(Int & a, Int b) {
    a -= b;
}

noinline void int_mul_set(Int & a, Int b) {
    a *= b;
}

noinline void int_div_set(Int & a, Int b) {
    a /= b;
}

noinline void int_mod_set(Int & a, Int b) {
    a %= b;
}

// op=(int64_t)
noinline void int_add_set(Int & a, int64_t b) {
    a += b;
}

noinline void int_sub_set(Int & a, int64_t b) {
    a -= b;
}

noinline void int_mul_set(Int & a, int64_t b) {
    a *= b;
}

noinline void int_div_set(Int & a, int64_t b) {
    a /= b;
}

noinline void int_mod_set(Int & a, int64_t b) {
    a %= b;
}

// op(Int, Int)
noinline Int int_add(Int a, Int b) {
    return a + b;
}

noinline Int int_sub(Int a, Int b) {
    return a - b;
}

noinline Int int_mul(Int a, Int b) {
    return a * b;
}

noinline Int int_div(Int a, Int b) {
    return a / b;
}

noinline Int int_mod(Int a, Int b) {
    return a % b;
}

// op(Int, int64_t)
noinline Int int_add(Int a, int64_t b) {
    return a + b;
}

noinline Int int_sub(Int a, int64_t b) {
    return a - b;
}

noinline Int int_mul(Int a, int64_t b) {
    return a * b;
}

noinline Int int_div(Int a, int64_t b) {
    return a / b;
}

noinline Int int_mod(Int a, int64_t b) {
    return a % b;
}

// op(int64_t, Int)
noinline Int int_add(int64_t a, Int b) {
    return a + b;
}

noinline Int int_sub(int64_t a, Int b) {
    return a - b;
}

noinline Int int_mul(int64_t a, Int b) {
    return a * b;
}

noinline Int int_div(int64_t a, Int b) {
    return a / b;
}

noinline Int int_mod(int64_t a, Int b) {
    return a % b;
}


