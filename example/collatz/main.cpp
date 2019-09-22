
#include <cinttypes>  // PRId64
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "crysp/long.hpp"
#include "crysp/double.hpp"

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

static CRYSP_NOINLINE constexpr uint64_t collatz_double(double n) {
    uint64_t iter = 0;
    for (; n > 1; iter++) {
        if ((long(n) & 1) != 0) {
            n = (n * 3 + 1);
        }
	n *= 0.5;
    }
    return iter;
}

static CRYSP_NOINLINE constexpr uint64_t collatz_Double(Double n) {
    uint64_t iter = 0;
    for (; n > 1; iter++) {
        if ((long(n.val()) & 1) != 0) {
            n = (n * 3 + 1);
        }
	n *= 0.5;
    }
    return iter;
}

template<class N, uint64_t (*func)(N) = collatz<N>>
static CRYSP_NOINLINE void collatz_repeat(N n) {
    uint64_t iter = 0;
    for (; n != 0; --n) {
        iter += func(n);
    }
    printf("%s: %" PRId64 "\n", __PRETTY_FUNCTION__, iter);
}

int main(int argc, const char * argv[]) {
    const char * typ = argc < 2 ? "Long" : argv[1];
    int64_t n = argc < 3 ? 12345678 : atoll(argv[2]);
    
    if (!strcmp(typ, "Long")) {
        collatz_repeat(Long{n});
    } else if (!strcmp(typ, "double")) {
        collatz_repeat<double, collatz_double>(double(n));
    } else if (!strcmp(typ, "Double")) {
        collatz_repeat<Double, collatz_Double>(Double(n));
    } else {
        collatz_repeat(long(n));
    }

    return 0;
}
