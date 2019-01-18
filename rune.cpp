
#include "rune.hpp"
#include "utf8.hpp"

int Rune::print(FILE *out) const {
    return utf8(utf8::make(i)).print(out);
}
