#ifndef CRYSP_INT_HPP
#define CRYSP_INT_HPP

#include "fixnum.hpp"

class Int : public Fixnum {
public:
    inline constexpr Int() noexcept
    /**/ : Fixnum{} {
    }

    explicit inline Int(int32_t i) noexcept
      : Fixnum{i, impl::fixnum_tag >> 32} {
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

extern const Int most_positive_int, most_negative_int;

#endif // CRYSP_INT_HPP
