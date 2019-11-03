
#include <cstdio>

#include "is.hpp"
#include "pair.hpp"
#include "new.hpp"
#include "nil.hpp"

CRYSP_NS_START

Pair::Pair(T first, T rest) /* throw(std::bad_alloc) */
    : T(impl::pair_tag | GCRYSP_NEW(pair, first, rest)) {
}

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
