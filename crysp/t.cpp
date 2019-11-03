#include <cstdio>

#include "double.hpp"
#include "float.hpp"
#include "func.hpp"
#include "nil.hpp"
#include "long.hpp"
#include "pair.hpp"
#include "rune.hpp"
#include "symbol.hpp"
#include "type.hpp"
#include "utf8.hpp"
#include "vector.hpp"

CRYSP_NS_START

int T::print(FILE *out) const {
    switch (type_id()) {
    case type::type_id:
        return reinterpret_cast<const Type *>(this)->print(out);
    case type::float_id:
        return reinterpret_cast<const Float *>(this)->print(out);
    case type::int_id:
        return reinterpret_cast<const Int *>(this)->print(out);
    case type::rune_id:
        return reinterpret_cast<const Rune *>(this)->print(out);
    case type::utf8_id:
        return reinterpret_cast<const Utf8 *>(this)->print(out);
    case type::double_id:
        return reinterpret_cast<const Double *>(this)->print(out);
    case type::long_id:
        return reinterpret_cast<const Long *>(this)->print(out);
    case type::obj_id:
        return fputs("obj", out);
    case type::pair_id:
        return reinterpret_cast<const Pair *>(this)->print(out);
    case type::symbol_id:
        return reinterpret_cast<const Symbol *>(this)->print(out);
    case type::vector_id:
        return reinterpret_cast<const Vector *>(this)->print(out);
    case type::func_id:
        return reinterpret_cast<const Func *>(this)->print(out);
    default:
        return fputs("unknown", out);
    }
}

CRYSP_NS_END
