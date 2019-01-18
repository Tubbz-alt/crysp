
#include <cinttypes>  // PRId32
#include <cstdio>

#include "crysp/short.hpp"

int Short::print(FILE *out) const {
    return fprintf(out, "%" PRId32, i);
}
