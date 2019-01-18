
#include <cstdio>

#include "crysp/float.hpp"

int Float::print(FILE *out) const {
    return fprintf(out, "%f", double(fl));
}
