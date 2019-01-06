#ifndef CRYSP_INT_HPP
#define CRYSP_INT_HPP

#include "fixnum.hpp"

class Int : public Fixnum {
public:
    inline constexpr Int() noexcept
    /**/ : Fixnum{} {
    }

    explicit constexpr inline Int(int32_t i) noexcept
        : Fixnum{uint64_t(int64_t(i)) | impl::fixnum_tag, bits_constructor{}} {
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
