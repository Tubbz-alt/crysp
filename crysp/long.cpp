
#include <cinttypes>  // PRId64
#include <cstdio>

#include "long.hpp"

CRYSP_NS_START

int Long::print(FILE *out) const {
    return fprintf(out, "%" PRId64, untag(bits));
}

CRYSP_NS_END
