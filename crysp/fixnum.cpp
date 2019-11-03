
#include <cinttypes>  // PRId64
#include <cstdio>

#include "fixnum.hpp"

CRYSP_NS_START

int Fixnum::print(FILE *out) const {
    return fprintf(out, "%" PRId64, untag(bits));
}

CRYSP_NS_END
