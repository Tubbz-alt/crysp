#ifndef CRYSP_NIL_HPP
#define CRYSP_NIL_HPP

#include "cons.hpp"

class Null : public Cons {
private:
    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return bits == impl::nil_bits;
    }

public:
    inline constexpr Null() noexcept : Cons(impl::nil_bits) {
    }

    /*
    inline constexpr Null(const Null & other) = default;
    inline constexpr Null & operator=(const Null & other) = default;
    inline ~Null() = default;
    */
};

constexpr Null nil;

#endif // CRYSP_NIL_HPP
