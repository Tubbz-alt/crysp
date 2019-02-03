
#include <cinttypes>  // PRId32
#include <cstdio>

#include "long.hpp"

CRYSP_NS_START

int Int::print(FILE *out) const {
    return fprintf(out, "%" PRId32, i);
}

CRYSP_NS_END
