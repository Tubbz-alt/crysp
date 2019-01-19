
#include "rune.hpp"
#include "utf8.hpp"

CRYSP_NS_START

int Rune::print(FILE *out) const {
    return utf8(utf8::make(i)).print(out);
}

CRYSP_NS_END

