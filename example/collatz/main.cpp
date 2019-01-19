
#include <cinttypes>  // PRId64
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "crysp/int.hpp"
#include "crysp/short.hpp"

CRYSP_NS_USE

template<class N>
static CRYSP_NOINLINE constexpr uint64_t collatz(N n) {
    uint64_t iter = 0;
    for (; n > 1; iter++) {
        if ((n & 1) != 0) {
            n = (n * 3 + 1);
        }
	n >>= 1; // faster than /= 2 when N is signed
    }
    return iter;
}

template<class N>
static CRYSP_NOINLINE void collatz_repeat(N n) {
    uint64_t iter = 0;
    for (; n != 0; --n) {
        iter += collatz(n);
    }
    printf("%s: %" PRId64 "\n", __PRETTY_FUNCTION__, iter);
}

int main(int argc, const char * argv[]) {
    const char * typ = argc < 2 ? "Int" : argv[1];
    int64_t n = argc < 3 ? 12345678 : atoll(argv[2]);
    
    if (!strcmp(typ, "Short")) {
        collatz_repeat(Short{int32_t(n)});
    } else if (!strcmp(typ, "Int")) {
        collatz_repeat(Int{n});
    } else if (!strcmp(typ, "int32")) {
        collatz_repeat(int32_t(n));
    } else {
        collatz_repeat(n);
    }

    return 0;
}
