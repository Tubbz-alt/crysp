#ifndef CRYSP_RUNE_HPP
#define CRYSP_RUNE_HPP

#include "t.hpp"

typedef int32_t rune; // Unicode is actually a little less than 21 bits

class Rune : public T {
public:
    inline constexpr Rune() noexcept
    /**/ : T{int32_t(0)} {
    }

    explicit inline constexpr Rune(rune ch) noexcept
    /**/ : T{ch} {
    }

    /*
    inline constexpr Rune(const Rune & other) = default;
    inline constexpr Rune & operator=(const Rune & other) = default;
    inline ~Rune() = default;
    */
    
    inline rune val() const noexcept {
        return i;
    }

    Rune & operator=(rune ch) noexcept {
        return (*this) = Rune{ch};
    }
};

#endif // CRYSP_RUNE_HPP
