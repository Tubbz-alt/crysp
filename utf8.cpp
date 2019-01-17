
#include <cstdio>

#include "utf8.hpp"

int Utf8::print_bits(FILE * out, uint32_t bits) {
    union utf8_union {
        uint32_t bits;
        char bytes[4];
    };
    utf8_union u = {bits};
    return fprintf(out, "%.4s", u.bytes);
}

int Utf8::print(FILE *out) const {
    return print_bits(out, i);
}
