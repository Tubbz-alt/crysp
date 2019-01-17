
#include <cstdio>

#include "double.hpp"

int Double::print(FILE *out) const {
    return fprintf(out, "%f", dbl);
}
