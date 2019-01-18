
#include <cstdio>

#include "crysp/double.hpp"

CRYSP_NS_START

int Double::print(FILE *out) const {
    return fprintf(out, "%f", dbl);
}

CRYSP_NS_END
