#ifndef CRYSP_SYMBOL_HPP
#define CRYSP_SYMBOL_HPP

#include "string.hpp"

CRYSP_NS_START

class Symbol : public T {
private:
    struct symbol {
        String name;
        T      value;
    };
    
    template<class E> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits & impl::pointer_mask) == impl::symbol_tag;
    }

    struct bits_constructor {};
    
    /* needed by t() */
    explicit inline constexpr Symbol(uint64_t bits,
                                     bits_constructor) noexcept
        : T(bits) {
    }

public:
    explicit Symbol(String name = String{}); /* throw(std::bad_alloc) */
        
    /*
    inline constexpr Symbol(const Symbol & other) = default;
    inline constexpr Symbol & operator=(const Symbol & other) = default;
    inline ~Symbol() = default;
    */

    static inline constexpr Type type() noexcept {
        return Type{type::symbol_id};
    }

    static inline constexpr type::id type_id() noexcept {
        return type::symbol_id;
    }

    enum {
          static_type_id = type::symbol_id,
    };

    int print(FILE *out) const;
    
    symbol * operator->() {
        return reinterpret_cast<symbol *>(addr());
    }

    const symbol * operator->() const {
        return reinterpret_cast<const symbol *>(addr());
    }

    // return a Symbol containing t
    static constexpr const Symbol t() {
        return Symbol{impl::t_bits, bits_constructor{}};
    }
};

constexpr const Symbol t = Symbol::t();

CRYSP_NS_END

#endif // CRYSP_SYMBOL_HPP
