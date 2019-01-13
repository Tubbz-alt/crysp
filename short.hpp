#ifndef CRYSP_SHORT_HPP
#define CRYSP_SHORT_HPP

#include "int.hpp"

class Short : public Int {
private:

    static inline uint64_t check(uint64_t bits) /* throw(std::bad_cast) */ {
        uint32_t hi = bits >> 32;
        if (hi != (impl::int_tag >> 32) && ~hi != 0) {
            impl::throw_bad_cast();
        }
        return bits;
    }

public:
    inline constexpr Short() noexcept
    /**/ : Int{} {
    }

    explicit constexpr inline Short(int32_t i) noexcept
        // sign-extend to 64 bits
        : Int{int64_t(i)} {
    }

    /*
    inline constexpr Short(const Short & other) = default;
    inline constexpr Short & operator=(const Short & other) = default;
    inline ~Short() = default;
    */
    
    inline constexpr int32_t val() const noexcept {
        return i;
    }

    Short & operator=(int32_t i) noexcept {
        return (*this) = Short{i};
    }
};

constexpr Short short_max{int32_t(0x7fffffffl)}, short_min{int32_t(-0x80000000l)};

#endif // CRYSP_SHORT_HPP
