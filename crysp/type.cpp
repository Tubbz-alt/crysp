
#include <cstdio>
#include <unordered_map>

#include "type.hpp"

CRYSP_NS_START

int Type::print(FILE *out) const {
    return fputs(name(), out);
}

const char * Type::name() const noexcept {
    static const char * const names[] =
        {
         "T", "Type", "Float", "Int", "Rune", "Utf8",
         nullptr, nullptr, nullptr, nullptr,
         nullptr, nullptr, nullptr, nullptr,
         "Double", "Long", "Struct", "Pair", "Symbol", "Func",
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
