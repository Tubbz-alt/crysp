#ifndef CRYSP_SMALLINT_HPP
#define CRYSP_SMALLINT_HPP

#include "fixint.hpp"

class Smallint : public Fixint {
private:

    static inline uint64_t check(uint64_t bits) /* throw(std::bad_cast) */ {
        uint32_t hi = bits >> 32;
        if (hi != (impl::fixint_tag >> 32) && ~hi != 0) {
            impl::throw_bad_cast();
        }
        return bits;
    }

public:
    inline constexpr Smallint() noexcept
    /**/ : Fixint{} {
    }

    explicit constexpr inline Smallint(int32_t i) noexcept
        // sign-extend to 64 bits
        : Fixint{int64_t(i)} {
    }

    /*
    inline constexpr Smallint(const Smallint & other) = default;
    inline constexpr Smallint & operator=(const Smallint & other) = default;
    inline ~Smallint() = default;
    */
    
    inline constexpr int32_t val() const noexcept {
        return i;
    }

    Smallint & operator=(int32_t i) noexcept {
        return (*this) = Smallint{i};
    }
};

constexpr Smallint smallint_max{int32_t(0x7fffffffl)}, smallint_min{int32_t(-0x80000000l)};

#endif // CRYSP_SMALLINT_HPP
