#ifndef CRYSP_NIL_HPP
#define CRYSP_NIL_HPP

#include "pair.hpp"

class Nil : public Pair {
private:
    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return bits == impl::nil_bits;
    }

public:
    inline constexpr Nil() noexcept
    : Pair(impl::nil_bits, bits_constructor{}) {
    }

    int print(FILE *out) const;

    /*
    inline constexpr Nil(const Nil & other) = default;
    inline constexpr Nil & operator=(const Nil & other) = default;
    inline ~Nil() = default;
    */
};

constexpr Nil nil;

#endif // CRYSP_NIL_HPP
