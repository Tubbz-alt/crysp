#ifndef CRYSP_INT_HPP
#define CRYSP_INT_HPP

#include "fixnum.hpp"

class Int : public Fixnum {
private:

    static inline uint64_t check(uint64_t bits) /* throw(std::bad_cast) */ {
        uint32_t hi = bits >> 32;
        if (hi != (impl::fixnum_tag >> 32) && ~hi != 0) {
            impl::throw_bad_cast();
        }
        return bits;
    }

public:
    inline constexpr Int() noexcept
    /**/ : Fixnum{} {
    }

    explicit constexpr inline Int(int32_t i) noexcept
        // sign-extend to 64 bits
        : Fixnum{uint64_t(int64_t(i)) | impl::fixnum_tag, bits_constructor{}} {
    }

    /* throws if argument is not an Int */
    explicit inline Int(T arg) /* throw(std::bad_cast) */
        : Fixnum{check(arg.bits), bits_constructor{}} {
    }

    /*
    inline constexpr Int(const Int & other) = default;
    inline constexpr Int & operator=(const Int & other) = default;
    inline ~Int() = default;
    */
    
    inline int32_t val() const noexcept {
        return i;
    }

    Int & operator=(int32_t i) noexcept {
        return (*this) = Int{i};
    }
};

constexpr Int most_positive_int{0x7fffffffl}, most_negative_int{-0x80000000l};

#endif // CRYSP_INT_HPP
