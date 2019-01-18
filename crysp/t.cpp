
#include <cstdio>
#include <cinttypes>  // PRId32, PRId64

#include "crysp/cast.hpp"
#include "crysp/int.hpp"
#include "crysp/float.hpp"
#include "crysp/nil.hpp"
#include "crysp/double.hpp"
#include "crysp/pair.hpp"
#include "crysp/rune.hpp"
#include "crysp/type.hpp"
#include "crysp/utf8.hpp"

CRYSP_NS_START

int T::print(FILE *out) const {
    switch (type_id()) {
    case type::float_id:
        return reinterpret_cast<const Float *>(this)->print(out);
    case type::short_id:
        return reinterpret_cast<const Short *>(this)->print(out);
    case type::type_id:
        return reinterpret_cast<const Type *>(this)->print(out);
    case type::rune_id:
        return reinterpret_cast<const Rune *>(this)->print(out);
    case type::utf8_id:
        return reinterpret_cast<const Utf8 *>(this)->print(out);
    case type::double_id:
        return reinterpret_cast<const Double *>(this)->print(out);
    case type::int_id:
        return reinterpret_cast<const Int *>(this)->print(out);
    case type::struct_id:
        return fputs("struct", out);
    case type::pair_id:
        return reinterpret_cast<const Pair *>(this)->print(out);
    case type::symbol_id:
        return fputs(bits == impl::t_bits ? "t" : "symbol", out);
    case type::func_id:
        return fputs("func", out);
    case type::unknown_id:
    default:
        return fputs("unknown", out);
    }
}

CRYSP_NS_END
