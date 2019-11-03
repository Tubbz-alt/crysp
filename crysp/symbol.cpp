#include "symbol.hpp"
#include "new.hpp"
#include "nil.hpp"

CRYSP_NS_START

Symbol::Symbol(String name) /* throw(std::bad_alloc) */
    // TODO intern with a map string -> symbol
    : T(impl::symbol_tag | GCRYSP_NEW(symbol, name, nil)) {
}

int Symbol::print(FILE *out) const {
    const symbol* s = reinterpret_cast<const symbol *>(addr());
    return s->name.print(out);
}
    
CRYSP_NS_END
