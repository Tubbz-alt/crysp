#include "double.hpp"

// op(Double, Double)
noinline Double double_add(Double a, Double b) {
    return a + b;
}

noinline Double double_sub(Double a, Double b) {
    return a - b;
}

noinline Double double_mul(Double a, Double b) {
    return a * b;
}

noinline Double double_div(Double a, Double b) {
    return a / b;
}


// op(Double, double)
noinline Double double_add(Double a, double b) {
    return a + b;
}

noinline Double double_sub(Double a, double b) {
    return a - b;
}

noinline Double double_mul(Double a, double b) {
    return a * b;
}

noinline Double double_div(Double a, double b) {
    return a / b;
}

// op(double, Double)
noinline Double double_add(double a, Double b) {
    return a + b;
}

noinline Double double_sub(double a, Double b) {
    return a - b;
}

noinline Double double_mul(double a, Double b) {
    return a * b;
}

noinline Double double_div(double a, Double b) {
    return a / b;
}
