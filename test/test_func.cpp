#include <cstdio>

#include "crysp/float.hpp"
#include "crysp/func.hpp"
#include "crysp/pair.hpp"

CRYSP_NS_USE

CRYSP_NOINLINE void nop() {
    fputs("Func: called nop()\n", stdout);
}

CRYSP_NOINLINE T identity(T arg) {
    fputs("Func: called identity() arguments = [", stdout);
    arg.print(stdout);
    fputs("]\n", stdout);
    return arg;
}

CRYSP_NOINLINE void test_func() {
    Func func{nop};
    Func::Ret ret = func();
    printf("Func: called nop() returned %u values\n", (unsigned)ret.size());

    Pair arg{Float{1.5f}, Float{2.0f}};
    func = Func{identity};
    ret = func(arg);
    fputs("Func: called identity() returned [", stdout);
    for (size_t i = 0, n = ret.size(); i < n; i++) {
        ret[i].print(stdout);
        fputs(", ", stdout);
    }
    fputs("]\n", stdout);
}

