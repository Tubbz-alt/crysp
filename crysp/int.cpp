
#include <cinttypes>  // PRId64
#include <cstdio>

#include "crysp/int.hpp"

CRYSP_NS_START

int Int::print(FILE *out) const {
    return fprintf(out, "%" PRId64, untag(bits));
}

CRYSP_NS_END
