
#include <cstdio>

#include "nil.hpp"

int Nil::print(FILE *out) const {
    return fputs("nil", out);
}
