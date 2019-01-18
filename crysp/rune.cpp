
#include "crysp/rune.hpp"
#include "crysp/utf8.hpp"

int Rune::print(FILE *out) const {
    return utf8(utf8::make(i)).print(out);
}
