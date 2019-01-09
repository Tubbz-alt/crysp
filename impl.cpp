
#include <cstdio>
#include <stdexcept> // std::overflow_error
#include <typeinfo>  // std::bad_cast

#include "fixnum.hpp"
#include "float.hpp"
#include "int.hpp"
#include "nil.hpp"
#include "double.hpp"

void impl::throw_bad_cast() /* throw(std::bad_cast) */ {
    throw std::bad_cast{};
}

void Fixnum::throw_overflow_error() /* throw(std::overflow_error) */ {
    throw std::overflow_error{"integer too large, overflows fixnum"};
}

void T::print(FILE *out) const {
    switch (bits >> 48) {
    case impl::float_tag >> 48:
        fprintf(out, "%f", double(fl));
        return;
    case impl::rune_tag >> 48:
        // FIXME print Unicode
        fprintf(out, "%c", char(i));
        return;
    case (impl::fixnum_tag >> 48) + 0:
    case (impl::fixnum_tag >> 48) + 1:
    case (impl::fixnum_tag >> 48) + 2:
    case (impl::fixnum_tag >> 48) + 3:
        fprintf(out, "%ld", Fixnum::untag(bits));
        return;
    }

    uint64_t addr52;
    
    if ((bits >> 52) == (impl::pointer_tag >> 52) &&
	(addr52 = (bits & ~impl::pointer_mask)) != 0 && /* skip +inf */
        addr52 != (uint64_t(1) << 51)) /* skip +NaN */ {

        switch (bits & 0xF) {
        case impl::struct_tag & 0xF:
            fputs("struct", out);
            break;
        case impl::cons_tag & 0xF:
            fputs(bits == impl::nil_bits ? "nil" : "cons", out);
            break;
        case impl::symbol_tag & 0xF:
            fputs(bits == impl::t_bits ? "t" : "symbol", out);
            break;
        case impl::func_tag & 0xF:
            fputs("func", out);
            break;
        default:
            fputs("unknown_pointer", out);
            break;
        }
        return;
    }
    fprintf(out, "%f", dbl);
}
