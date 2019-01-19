
#include <cstdio>

#include "utf8.hpp"

CRYSP_NS_START

int utf8::print(FILE *out) const {
    return fprintf(out, "%.4s", byte);
}

CRYSP_NS_END
