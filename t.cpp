
#include <cstdio>
#include <cinttypes>  // PRId32, PRId64

#include "cast.hpp"
#include "int.hpp"
#include "float.hpp"
#include "nil.hpp"
#include "double.hpp"
#include "pair.hpp"
#include "rune.hpp"

type_id T::type() const noexcept {
    switch (bits >> 48) {
    case impl::float_tag >> 48:
        return float_id;
    case impl::short_tag >> 48:
        return short_id;
    case impl::rune_tag >> 48:
        return rune_id;
    case (impl::int_tag >> 48) + 0:
    case (impl::int_tag >> 48) + 1:
    case (impl::int_tag >> 48) + 2:
    case (impl::int_tag >> 48) + 3:
        return int_id;
    }

    uint64_t addr52 = 0;

    if ((bits >> 52) == (impl::pointer_tag >> 52) &&
	(addr52 = (bits & ~impl::pointer_mask)) != 0 && /* skip +inf */
        addr52 != (uint64_t(1) << 51)) /* skip +NaN */ {

        switch (bits & 0xF) {
        case impl::struct_tag & 0xF:
            return struct_id;
        case impl::pair_tag & 0xF:
            return pair_id;
        case impl::symbol_tag & 0xF:
            return symbol_id;
        case impl::func_tag & 0xF:
            return func_id;
        default:
            return unknown_id;
        }
    }
    return double_id;
}

int T::print(FILE *out) const {
    switch (type()) {
    case double_id:
        return fprintf(out, "%f", dbl);
    case int_id:
        return fprintf(out, "%" PRId64, Int::untag(bits));
    case float_id:
        return fprintf(out, "%f", double(fl));
    case short_id:
        return fprintf(out, "%" PRId32, i);
    case rune_id:
        return fprintf(out, "%.4s", utf8_t(i).byte);
    case struct_id:
        return fputs("struct", out);
    case pair_id:
        if (bits == impl::nil_bits) {
            return fputs("nil", out);
        } else {
            Pair p = cast<Pair>(*this);
            int ret = 4;
            fputc('(', out);
            ret += p->first.print(out);
            fputs(", ", out);
            ret += p->second.print(out);
            fputc(')', out);
            return ret;
        }
    case symbol_id:
        return fputs(bits == impl::t_bits ? "t" : "symbol", out);
    case func_id:
        return fputs("func", out);
    case unknown_id:
    default:
        return fputs("unknown", out);
    }
}
