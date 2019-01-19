
#include <cinttypes>  // PRId32
#include <cstdio>

#include "short.hpp"

CRYSP_NS_START

int Short::print(FILE *out) const {
    return fprintf(out, "%" PRId32, i);
}

CRYSP_NS_END
