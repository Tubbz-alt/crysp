
#include <cstdio>

#include "rune.hpp"
#include "utf8.hpp"

int Rune::print(FILE *out) const {
    return Utf8::print_bits(out, Utf8::make(i));
}
