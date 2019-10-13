#include <cstdio>

#include "crysp/double.hpp"
#include "crysp/float.hpp"
#include "crysp/int.hpp"
#include "crysp/rune.hpp"
#include "crysp/utf8.hpp"
#include "crysp/values.hpp"

CRYSP_NS_USE

CRYSP_NOINLINE Values<> values0() {
    return values();
}

CRYSP_NOINLINE Values<Double> values1() {
    return values(Double{1.0});
}

CRYSP_NOINLINE Values<Rune, Utf8> values2() {
    return values(Rune{'!'}, Utf8{'!'});
}

CRYSP_NOINLINE Values<Float, Double, T> values3() {
    return values(Float{9.5f}, Double{'!'}, t);
}

CRYSP_NOINLINE void test_values() {
    values0();
    fputs("Values: called values0()\n", stdout);
    values1();
    fputs("Values: called values1()\n", stdout);
    values2();
    fputs("Values: called values2()\n", stdout);
    values3();
    fputs("Values: called values3()\n", stdout);
}

