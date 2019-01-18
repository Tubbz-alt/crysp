
#include <cstdio>

#include "crysp/nil.hpp"

CRYSP_NS_START

int Nil::print(FILE *out) const {
    return fputs("nil", out);
}

CRYSP_NS_END
