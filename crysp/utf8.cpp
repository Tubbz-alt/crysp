
#include <cstdio>

#include "crysp/utf8.hpp"

int utf8::print(FILE *out) const {
    return fprintf(out, "%.4s", byte);
}

