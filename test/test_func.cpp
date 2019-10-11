#include <cstdio>

#include "crysp/func.hpp"

CRYSP_NS_USE

CRYSP_NOINLINE void foo() {
    fputs("Func: called foo()\n", stdout);
}

CRYSP_NOINLINE void test_func() {
    Func func{foo};
    func();
}

