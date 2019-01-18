
#include <cstdio>

#include "crysp/nil.hpp"

int Nil::print(FILE *out) const {
    return fputs("nil", out);
}
