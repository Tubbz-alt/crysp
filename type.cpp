
#include <cstdio>

#include "type.hpp"

const char * Type::name() const noexcept {
    switch (id_) {
    case double_id:
        return "Double";
    case int_id:
        return "Int";
    case float_id:
        return "Float";
    case short_id:
        return "Short";
    case rune_id:
        return "Rune";
    case struct_id:
        return "Struct";
    case pair_id:
        return "Pair";
    case symbol_id:
        return "Symbol";
    case func_id:
        return "Func";
    case unknown_id:
    default:
        return "unknown";
    }
}
