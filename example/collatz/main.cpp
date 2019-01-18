
#include <cstdio>
#include <cinttypes>  // PRId64
#include <cstdlib>

#include "crysp/int.hpp"

CRYSP_NS_USE

template<class N>
static CRYSP_NOINLINE constexpr uint64_t collatz(N n) {
    uint64_t iter = 0;
    for (; n > 1; iter++) {
        if ((n & 1) != 0) {
            n = (n * 3 + 1) >> 1; // >> 1 is faster than / 2 when N is signed
        } else {
            n >>= 1; // idem
        }
    }
    return iter;
}

static int argcount = 1;

template<class N>
static CRYSP_NOINLINE void collatz_repeat(N n, size_t count) {
    uint64_t iter = 0;
    for (; count != 0; count--) {
        iter = collatz(n);
        if (argcount == 0)
            printf("%" PRId64 "\n", iter);
    }
    printf("%s: %" PRId64 "\n", __PRETTY_FUNCTION__, iter);
}

int main(int argc, const char * argv[]) {
    int64_t n = argc < 2 ? 0x123456789ABull : atoll(argv[1]);

    argcount = argc;

    if (argc < 3) {
        collatz_repeat(n,      10000000);
    } else {
        collatz_repeat(Int{n}, 10000000);
    }

    return 0;
}
