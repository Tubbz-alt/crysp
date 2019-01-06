#ifndef CRYSP_NIL_HPP
#define CRYSP_NIL_HPP

#include "t.hpp"

class Null : public T {
public:
    inline constexpr Null() noexcept : T(impl::nil_bits) {
    }

    /*
    inline constexpr Null(const Null & other) = default;
    inline constexpr Null & operator=(const Null & other) = default;
    inline ~Null() = default;
    */

    inline operator bool() const noexcept {
        return false;
    }
};

constexpr Null nil;

#endif // CRYSP_NIL_HPP
