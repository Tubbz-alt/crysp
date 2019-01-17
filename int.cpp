
#include <cinttypes>  // PRId64
#include <cstdio>

#include "int.hpp"

int Int::print(FILE *out) const {
    return fprintf(out, "%" PRId64, untag(bits));
}
