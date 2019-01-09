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
    
    static void throw_overflow_error(); /* throw(std::overflow_error) */

    /*
     * int64_t -> Fixnum conversion, modulo 2^50:
     * wraps around if argument overflows Fixnum
     */
    static inline constexpr uint64_t tag(int64_t i) noexcept {
        return uint64_t(i) | impl::fixnum_tag;
    }

    /*
     * checked int64_t -> Fixnum conversion. throws std::overflow_error
     * if argument overflows Fixnum (50 bits)
    */
    static inline uint64_t tag(int64_t i, check_overflow_t) /* throw(std::overflow_error) */ {
        uint32_t hi = uint64_t(i) >> payload_nbits;
        if (hi != 0 && hi != 0x3FFF) {
            throw_overflow_error();
        }
        return uint64_t(i) | impl::fixnum_tag;
    }

    static inline constexpr int64_t untag(uint64_t bits) noexcept {
        return int64_t(bits << tag_nbits) >> tag_nbits;
    }

    static inline uint64_t check(uint64_t bits) /* throw(std::bad_cast) */ {
        uint32_t hi = ~bits >> payload_nbits;
        if (hi != 0) {
            impl::throw_bad_cast();
        }
        return bits;
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

    /* 
     * unchecked constructor: wraps around modulo 2^50
     * if argument overflows Fixnum (50 bits)
     */
    explicit inline constexpr Fixnum(int64_t i) noexcept
    /**/ : T{tag(i)} {
    }

    /*
     * checked constructor: throws std::overflow_error
     * if argument overflows Fixnum (50 bits)
     */
    explicit inline Fixnum(int64_t i, check_overflow_t chk) /* throw(std::overflow_error) */
        /**/ : T{tag(i, chk)} {
    }

    /* throws std::bad_cast if argument dynamic type is not Fixnum */
    explicit inline Fixnum(T arg) /* throw(std::bad_cast) */
    /**/ : T{check(arg.bits)} {
    }

    /*
    inline constexpr Fixnum(const Fixnum & other) = default;
    inline constexpr Fixnum & operator=(const Fixnum & other) = default;
    inline ~Fixnum() = default;
    */
    
    inline constexpr int64_t val() const noexcept {
        return untag(bits);
    }

    /* wraps around modulo 2^50: Fixnum only holds 50 bits */
    inline constexpr Fixnum & operator=(int64_t i) noexcept {
        return (*this) = Fixnum{i};
    }

    /* less than */
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
    inline constexpr Fixnum operator-() noexcept {
        return Fixnum{-bits | impl::fixnum_tag,
                bits_constructor{}};
    }

    /* boolean negate */
    inline constexpr Fixnum operator!() noexcept {
        return Fixnum{(bits == impl::fixnum_tag) | impl::fixnum_tag,
                bits_constructor{}};
    }

    /* add */
    inline constexpr Fixnum & operator+=(Fixnum other) noexcept {
        bits = (bits + other.bits) | impl::fixnum_tag;
        return *this;
    }

    inline constexpr Fixnum & operator+=(int64_t other) noexcept {
        bits = (bits + other) | impl::fixnum_tag;
        return *this;
    }

    /* subtract */
    inline constexpr Fixnum & operator-=(Fixnum other) noexcept {
        bits = (bits - other.bits) | impl::fixnum_tag;
        return *this;
    }

    inline constexpr Fixnum & operator-=(int64_t other) noexcept {
        bits = (bits - other) | impl::fixnum_tag;
        return *this;
    }

    /* multiply */
    inline constexpr Fixnum & operator*=(Fixnum other) noexcept {
        // no need to untag(bits)
        int64_t i = int64_t(bits), j = untag(other.bits);
        bits = uint64_t(i * j) | impl::fixnum_tag;
        return *this;
    }

    inline constexpr Fixnum & operator*=(int64_t other) noexcept {
        // no need to untag(bits)
        int64_t i = int64_t(bits), j = other;
        bits = uint64_t(i * j) | impl::fixnum_tag;
        return *this;
    }

    /* divide */
    inline constexpr Fixnum & operator/=(Fixnum other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i / j) | impl::fixnum_tag;
        return *this;
    }

    inline constexpr Fixnum & operator/=(int64_t other) noexcept {
        int64_t i = untag(bits), j = other;
        bits = uint64_t(i / j) | impl::fixnum_tag;
        return *this;
    }

    /* modulus */
    inline constexpr Fixnum & operator%=(Fixnum other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i % j) | impl::fixnum_tag;
        return *this;
    }

    inline constexpr Fixnum & operator%=(int64_t other) noexcept {
        int64_t i = untag(bits), j = other;
        bits = uint64_t(i % j) | impl::fixnum_tag;
        return *this;
    }

    /* bitwise complement */
    inline constexpr Fixnum operator~() noexcept {
        return Fixnum{~bits | impl::fixnum_tag,
                bits_constructor{}};
    }

    /* bitwise and */
    inline constexpr Fixnum & operator&=(Fixnum other) noexcept {
        bits = (bits & other.bits) | impl::fixnum_tag;
        return *this;
    }

    inline constexpr Fixnum & operator&=(int64_t other) noexcept {
        bits = (bits & other) | impl::fixnum_tag;
        return *this;
    }

    /* bitwise or */
    inline constexpr Fixnum & operator|=(Fixnum other) noexcept {
        bits = (bits | other.bits) | impl::fixnum_tag;
        return *this;
    }

    inline constexpr Fixnum & operator|=(int64_t other) noexcept {
        bits = (bits | other) | impl::fixnum_tag;
        return *this;
    }

    /* bitwise xor */
    inline constexpr Fixnum & operator^=(Fixnum other) noexcept {
        bits = (bits ^ other.bits) | impl::fixnum_tag;
        return *this;
    }

    inline constexpr Fixnum & operator^=(int64_t other) noexcept {
        bits = (bits ^ other) | impl::fixnum_tag;
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


/* op(Fixnum, Fixnum) */

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

inline constexpr Fixnum operator%(Fixnum a, Fixnum b) noexcept {
    return a %= b;
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



/* op(Fixnum, int64_t) */

// correct also if a overflows Fixnum
inline constexpr bool operator<(Fixnum a, int64_t b) noexcept {
    return a.val() < b;
}

// correct also if a overflows Fixnum
inline constexpr bool operator>(Fixnum a, int64_t b) noexcept {
    return a.val() > b;
}

// correct also if a overflows Fixnum
inline constexpr bool operator<=(Fixnum a, int64_t b) noexcept {
    return a.val() <= b;
}

// correct also if a overflows Fixnum
inline constexpr bool operator>=(Fixnum a, int64_t b) noexcept {
    return a.val() >= b;
}


inline constexpr Fixnum operator+(Fixnum a, int64_t b) noexcept {
    return a += b;
}

inline constexpr Fixnum operator-(Fixnum a, int64_t b) noexcept {
    return a -= b;
}

inline constexpr Fixnum operator*(Fixnum a, int64_t b) noexcept {
    return a *= b;
}

inline constexpr Fixnum operator/(Fixnum a, int64_t b) noexcept {
    return a /= b;
}

inline constexpr Fixnum operator%(Fixnum a, int64_t b) noexcept {
    return a %= b;
}



inline constexpr Fixnum operator&(Fixnum a, int64_t b) noexcept {
    return a &= b;
}

inline constexpr Fixnum operator|(Fixnum a, int64_t b) noexcept {
    return a |= b;
}

inline constexpr Fixnum operator^(Fixnum a, int64_t b) noexcept {
    return a ^= b;
}




/* op(int64_t, Fixnum) */

// correct also if a overflows Fixnum
inline constexpr bool operator<(int64_t a, Fixnum b) noexcept {
    return a < b.val();
}

// correct also if a overflows Fixnum
inline constexpr bool operator>(int64_t a, Fixnum b) noexcept {
    return a > b.val();
}

// correct also if a overflows Fixnum
inline constexpr bool operator<=(int64_t a, Fixnum b) noexcept {
    return a <= b.val();
}

// correct also if a overflows Fixnum
inline constexpr bool operator>=(int64_t a, Fixnum b) noexcept {
    return a >= b.val();
}


inline constexpr Fixnum operator+(int64_t a, Fixnum b) noexcept {
    return b += a;
}

inline constexpr Fixnum operator-(int64_t a, Fixnum b) noexcept {
    return Fixnum{int64_t(a - b.debug_bits())};
}

inline constexpr Fixnum operator*(int64_t a, Fixnum b) noexcept {
    return b *= a;
}

inline constexpr Fixnum operator/(int64_t a, Fixnum b) noexcept {
    return Fixnum{a / b.val()};
}

inline constexpr Fixnum operator%(int64_t a, Fixnum b) noexcept {
    return Fixnum{a % b.val()};
}



inline constexpr Fixnum operator&(int64_t a, Fixnum b) noexcept {
    return b &= a;
}

inline constexpr Fixnum operator|(int64_t a, Fixnum b) noexcept {
    return b |= a;
}

inline constexpr Fixnum operator^(int64_t a, Fixnum b) noexcept {
    return b ^= a;
}


constexpr Fixnum most_positive_fixnum{ 0x1ffffffffffffll};
constexpr Fixnum most_negative_fixnum{-0x2000000000000ll};

#endif // CRYSP_FIXNUM_HPP
