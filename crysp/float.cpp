
#include <cstdio>

#include "crysp/float.hpp"

CRYSP_NS_START

int Float::print(FILE *out) const {
    return fprintf(out, "%f", double(fl));
}

CRYSP_NS_END
