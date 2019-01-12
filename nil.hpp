#ifndef CRYSP_NIL_HPP
#define CRYSP_NIL_HPP

#include "cons.hpp"

class Nil : public Cons {
private:
    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return bits == impl::nil_bits;
    }

public:
    inline constexpr Nil() noexcept
    : Cons(impl::nil_bits, bits_constructor{}) {
    }

    /*
    inline constexpr Nil(const Nil & other) = default;
    inline constexpr Nil & operator=(const Nil & other) = default;
    inline ~Nil() = default;
    */
};

constexpr Nil nil;

#endif // CRYSP_NIL_HPP
