
#include <cstdio>

#include "float.hpp"

int Float::print(FILE *out) const {
    return fprintf(out, "%f", double(fl));
}
