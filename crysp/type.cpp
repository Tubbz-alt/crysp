
#include <cstdio>

#include "type.hpp"

CRYSP_NS_START

int Type::print(FILE *out) const {
    return fputs(name(), out);
}

const char * Type::name() const noexcept {
    switch (type::id(i)) {
    case type::type_id:
        return "Type";
    case type::float_id:
        return "Float";
    case type::int_id:
        return "Int";
    case type::rune_id:
        return "Rune";
    case type::utf8_id:
        return "Utf8";
    case type::double_id:
        return "Double";
    case type::long_id:
        return "Long";
    case type::struct_id:
        return "Struct";
    case type::pair_id:
        return "Pair";
    case type::symbol_id:
        return "Symbol";
    case type::func_id:
        return "Func";
    case type::unknown_id:
    default:
        return "Unknown";
    }
}

CRYSP_NS_END
