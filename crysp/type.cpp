
#include <cstdio>
#include <unordered_map>

#include "type.hpp"

CRYSP_NS_START

int Type::print(FILE *out) const {
    return fputs(name(), out);
}

const char * Type::name() const noexcept {
    static_assert(type::t_id       == 0 &&
                  type::type_id    == 1 &&
                  type::float_id   == 2 &&
                  type::int_id     == 3 &&
                  type::rune_id    == 4 &&
                  type::utf8_id    == 5 &&
                  type::double_id  == 0xE &&
                  type::fixnum_id  == 0xF &&
                  type::obj_id     == 0x10 &&
                  type::pair_id    == 0x11 &&
                  type::symbol_id  == 0x12 &&
                  type::func_id    == 0x13,
                  "type::id enum values changed. update Type::name() accordingly");
    
    static const char * const names[] =
        {
         "T", "Type", "Float", "Int", "Rune", "Utf8",
         nullptr, nullptr, nullptr, nullptr,
         nullptr, nullptr, nullptr, nullptr,
         "Double", "Fixnum", "Obj", "Pair", "Symbol", "Func",
        };
    if (size_t(i) < sizeof(names)/sizeof(names[0])) {
        const char * ret = names[size_t(i)];
        if (ret != nullptr) {
            return ret;
        }
    }
    return "Unknown";
}

CRYSP_NS_END
