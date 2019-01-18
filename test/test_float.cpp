#include "crysp/float.hpp"

CRYSP_NS_USE

// op=(Float)
CRYSP_NOINLINE void float_add_set(Float & a, Float b) {
    a += b;
}

CRYSP_NOINLINE void float_sub_set(Float & a, Float b) {
    a -= b;
}

CRYSP_NOINLINE void float_mul_set(Float & a, Float b) {
    a *= b;
}

CRYSP_NOINLINE void float_div_set(Float & a, Float b) {
    a /= b;
}


// op(Float, Float)
CRYSP_NOINLINE Float float_add(Float a, Float b) {
    return a + b;
}

CRYSP_NOINLINE Float float_sub(Float a, Float b) {
    return a - b;
}

CRYSP_NOINLINE Float float_mul(Float a, Float b) {
    return a * b;
}

CRYSP_NOINLINE Float float_div(Float a, Float b) {
    return a / b;
}


// op(Float, float)
CRYSP_NOINLINE Float float_add(Float a, float b) {
    return a + b;
}

CRYSP_NOINLINE Float float_sub(Float a, float b) {
    return a - b;
}

CRYSP_NOINLINE Float float_mul(Float a, float b) {
    return a * b;
}

CRYSP_NOINLINE Float float_div(Float a, float b) {
    return a / b;
}

// op(float, Float)
CRYSP_NOINLINE Float float_add(float a, Float b) {
    return a + b;
}

CRYSP_NOINLINE Float float_sub(float a, Float b) {
    return a - b;
}

CRYSP_NOINLINE Float float_mul(float a, Float b) {
    return a * b;
}

CRYSP_NOINLINE Float float_div(float a, Float b) {
    return a / b;
}


