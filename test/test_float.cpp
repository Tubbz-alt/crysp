#include "crysp/float.hpp"

// op=(Float)
noinline void float_add_set(Float & a, Float b) {
    a += b;
}

noinline void float_sub_set(Float & a, Float b) {
    a -= b;
}

noinline void float_mul_set(Float & a, Float b) {
    a *= b;
}

noinline void float_div_set(Float & a, Float b) {
    a /= b;
}


// op(Float, Float)
noinline Float float_add(Float a, Float b) {
    return a + b;
}

noinline Float float_sub(Float a, Float b) {
    return a - b;
}

noinline Float float_mul(Float a, Float b) {
    return a * b;
}

noinline Float float_div(Float a, Float b) {
    return a / b;
}


// op(Float, float)
noinline Float float_add(Float a, float b) {
    return a + b;
}

noinline Float float_sub(Float a, float b) {
    return a - b;
}

noinline Float float_mul(Float a, float b) {
    return a * b;
}

noinline Float float_div(Float a, float b) {
    return a / b;
}

// op(float, Float)
noinline Float float_add(float a, Float b) {
    return a + b;
}

noinline Float float_sub(float a, Float b) {
    return a - b;
}

noinline Float float_mul(float a, Float b) {
    return a * b;
}

noinline Float float_div(float a, Float b) {
    return a / b;
}


