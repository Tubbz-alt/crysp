#ifndef CRYSP_FIXNUM_HPP
#define CRYSP_FIXNUM_HPP

#include "t.hpp"

class Fixnum : public T {
private:
    friend class T;

    enum {
        tag_nbits = 14,
        payload_nbits = 50,
    };
    
    static void fixnum_range_error(); /* throw(std::range_error) */
    
    static inline uint64_t tag(int64_t i) /* throw(std::range_error) */ {
        uint32_t hi = uint64_t(i) >> payload_nbits;
        if (hi != 0 && hi != 0x3FFF) {
            fixnum_range_error();
        }
        return uint64_t(i) | impl::fixnum_tag;
    }

    static inline constexpr int64_t untag(uint64_t bits) noexcept {
        return int64_t(bits << tag_nbits) >> tag_nbits;
    }

protected:
    struct bits_constructor {};
    
    /* needed by subclass constructor Int(int32_t) */
    inline constexpr Fixnum(uint64_t bits, bits_constructor) noexcept
    /**/ : T{bits} {
    }
        
    
public:
    inline constexpr Fixnum() noexcept
    /**/ : T{uint64_t(impl::fixnum_tag)} {
    }

    /* may throw: Fixnum only holds 50 bits */
    explicit inline Fixnum(int64_t i) /* throw(std::range_error) */
    /**/ : T{tag(i)} {
    }

    /*
    inline constexpr Fixnum(const Fixnum & other) = default;
    inline constexpr Fixnum & operator=(const Fixnum & other) = default;
    inline ~Fixnum() = default;
    */
    
    inline constexpr int64_t val() const noexcept {
        return untag(bits);
    }

    /* may throw: Fixnum only holds 50 bits */
    inline Fixnum & operator=(int64_t i) /* throw(std::range_error) */ {
        return (*this) = Fixnum{i};
    }

    inline constexpr bool operator<(Fixnum other) noexcept {
        return (int64_t(bits) << tag_nbits)
             < (int64_t(other.bits) << tag_nbits);
    }
    
    /* pre-increment */
    inline constexpr Fixnum & operator++() noexcept {
        bits = (bits + 1) | impl::fixnum_tag;
        return *this;
    }

    /* post-increment */
    inline constexpr Fixnum operator++(int) noexcept {
        Fixnum ret = *this;
        bits = (bits + 1) | impl::fixnum_tag;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Fixnum & operator--() noexcept {
        bits = (bits - 1) | impl::fixnum_tag;
        return *this;
    }

    /* post-decrement */
    inline constexpr Fixnum operator--(int) noexcept {
        Fixnum ret = *this;
        bits = (bits - 1) | impl::fixnum_tag;
        return ret;
    }

    /* identity */
    inline constexpr Fixnum & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Fixnum & operator-() noexcept {
        bits = -bits | impl::fixnum_tag;
        return *this;
    }

    /* boolean negate. equivalent to == 0 */
    inline constexpr Fixnum & operator!() noexcept {
        bits = uint64_t(bits == impl::fixnum_tag) | impl::fixnum_tag;
        return *this;
    }

    /* add */
    inline constexpr Fixnum & operator+=(Fixnum other) noexcept {
        bits = (bits + other.bits) | impl::fixnum_tag;
        return *this;
    }

    /* subtract */
    inline constexpr Fixnum & operator-=(Fixnum other) noexcept {
        bits = (bits - other.bits) | impl::fixnum_tag;
        return *this;
    }

    /* multiply */
    inline constexpr Fixnum & operator*=(Fixnum other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i * j) | impl::fixnum_tag;
        return *this;
    }

    /* divide */
    inline constexpr Fixnum & operator/=(Fixnum other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i / j) | impl::fixnum_tag;
        return *this;
    }

    /* bitwise complement */
    inline constexpr Fixnum & operator~() noexcept {
        bits = ~bits | impl::fixnum_tag;
        return *this;
    }

    /* bitwise and */
    inline constexpr Fixnum & operator&=(Fixnum other) noexcept {
        bits = (bits & other.bits) | impl::fixnum_tag;
        return *this;
    }

    /* bitwise or */
    inline constexpr Fixnum & operator|=(Fixnum other) noexcept {
        bits = (bits | other.bits) | impl::fixnum_tag;
        return *this;
    }

    /* bitwise xor */
    inline constexpr Fixnum & operator^=(Fixnum other) noexcept {
        bits = (bits ^ other.bits) | impl::fixnum_tag;
        return *this;
    }

    /* bitwise lshift */
    inline constexpr Fixnum & operator<<=(uint8_t count) noexcept {
        bits = (bits << count) | impl::fixnum_tag;
        return *this;
    }

    /* bitwise rshift */
    inline constexpr Fixnum & operator>>=(uint8_t count) noexcept {
        int64_t i = untag(bits);
        // shift separately from the shift performed by untag() above,
        // to avoid undefined behaviour if count >= 50
        i >>= count;
        bits = uint64_t(i) | impl::fixnum_tag;
        return *this;
    }
};


inline constexpr bool operator>(Fixnum a, Fixnum b) noexcept {
    return b < a;
}

inline constexpr bool operator<=(Fixnum a, Fixnum b) noexcept {
    return !(b < a);
}

inline constexpr bool operator>=(Fixnum a, Fixnum b) noexcept {
    return !(a < b);
}



inline constexpr Fixnum operator+(Fixnum a, Fixnum b) noexcept {
    return a += b;
}

inline constexpr Fixnum operator-(Fixnum a, Fixnum b) noexcept {
    return a -= b;
}

inline constexpr Fixnum operator*(Fixnum a, Fixnum b) noexcept {
    return a *= b;
}

inline constexpr Fixnum operator/(Fixnum a, Fixnum b) noexcept {
    return a /= b;
}



inline constexpr Fixnum operator&(Fixnum a, Fixnum b) noexcept {
    return a &= b;
}

inline constexpr Fixnum operator|(Fixnum a, Fixnum b) noexcept {
    return a |= b;
}

inline constexpr Fixnum operator^(Fixnum a, Fixnum b) noexcept {
    return a ^= b;
}

inline constexpr Fixnum operator<<(Fixnum a, uint8_t b) noexcept {
    return a <<= b;
}

inline constexpr Fixnum operator>>(Fixnum a, uint8_t b) noexcept {
    return a >>= b;
}

extern const Fixnum most_positive_fixnum, most_negative_fixnum;

#endif // CRYSP_FIXNUM_HPP
