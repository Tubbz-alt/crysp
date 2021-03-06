#include "crysp/double.hpp"

CRYSP_NS_USE

// op=(Double)
CRYSP_NOINLINE void double_add_ref(Double & a, Double b) {
    a += b;
}

CRYSP_NOINLINE void double_sub_ref(Double & a, Double b) {
    a -= b;
}

CRYSP_NOINLINE void double_mul_ref(Double & a, Double b) {
    a *= b;
}

CRYSP_NOINLINE void double_div_ref(Double & a, Double b) {
    a /= b;
}

// op(Double, Double)
CRYSP_NOINLINE Double double_add(Double a, Double b) {
    return a + b;
}

CRYSP_NOINLINE Double double_sub(Double a, Double b) {
    return a - b;
}

CRYSP_NOINLINE Double double_mul(Double a, Double b) {
    return a * b;
}

CRYSP_NOINLINE Double double_div(Double a, Double b) {
    return a / b;
}


// op(Double, double)
CRYSP_NOINLINE Double double_add(Double a, double b) {
    return a + b;
}

CRYSP_NOINLINE Double double_sub(Double a, double b) {
    return a - b;
}

CRYSP_NOINLINE Double double_mul(Double a, double b) {
    return a * b;
}

CRYSP_NOINLINE Double double_div(Double a, double b) {
    return a / b;
}

// op(double, Double)
CRYSP_NOINLINE Double double_add(double a, Double b) {
    return a + b;
}

CRYSP_NOINLINE Double double_sub(double a, Double b) {
    return a - b;
}

CRYSP_NOINLINE Double double_mul(double a, Double b) {
    return a * b;
}

CRYSP_NOINLINE Double double_div(double a, Double b) {
    return a / b;
}
