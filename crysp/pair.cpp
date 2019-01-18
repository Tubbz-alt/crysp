
#include <cstdio>

#include "crysp/pair.hpp"
#include "crysp/nil.hpp"

CRYSP_NS_START

int Pair::print(FILE *out) const {
    if (bits == impl::nil_bits) {
        return reinterpret_cast<const Nil *>(this)->print(out);
    }
    const pair * p = operator->();
    int ret = 4;
    fputc('(', out);
    ret += p->first.print(out);
    fputs(", ", out);
    ret += p->second.print(out);
    fputc(')', out);
    return ret;
}

CRYSP_NS_END
