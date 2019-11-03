
#include <cstdio>

#include "is.hpp"
#include "pair.hpp"
#include "nil.hpp"

CRYSP_NS_START

int Pair::print(FILE *out) const {
    Pair P = *this;
    if (P == nil) {
        return nil.print(out);
    }
    int ret = 2;
    fputc('(', out);
    for (;;) {
        const pair * p = P.operator->();
        ret += p->first.print(out);
        T rest = p->rest;
        if (rest == nil) {
            break;
        } else if (is<Pair>(rest, &P)) {
            fputc(' ', out);
            continue;
        } else {
            fputs(" . ", out);
            ret += 3 + rest.print(out);
            break;
        }
    }
    fputc(')', out);
    return ret;
}

CRYSP_NS_END
