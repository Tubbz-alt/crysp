#ifndef CRYSP_FIXINT_HPP
#define CRYSP_FIXINT_HPP

#include "t.hpp"

class Fixint : public T {
private:
    friend class T;
    template<class To> friend bool is(T arg);

    enum {
        tag_nbits = 14,
        payload_nbits = 50,
    };
    
    static void throw_overflow_error(); /* throw(std::overflow_error) */

    /*
     * int64_t -> Fixint conversion, modulo 2^50:
     * wraps around if argument overflows Fixint
     */
    static inline constexpr uint64_t tag(int64_t i) noexcept {
        return uint64_t(i) | impl::fixint_tag;
    }

    /*
     * checked int64_t -> Fixint conversion. throws std::overflow_error
     * if argument overflows Fixint (50 bits)
    */
    static inline uint64_t tag(int64_t i, check_overflow_t) /* throw(std::overflow_error) */ {
        uint32_t hi = uint64_t(i) >> payload_nbits;
        if (hi != 0 && hi != 0x3FFF) {
            throw_overflow_error();
        }
        return uint64_t(i) | impl::fixint_tag;
    }

    static inline constexpr int64_t untag(uint64_t bits) noexcept {
        return int64_t(bits << tag_nbits) >> tag_nbits;
    }

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (~bits >> payload_nbits) == 0;
    }

public:
    inline constexpr Fixint() noexcept
    /**/ : T{uint64_t(impl::fixint_tag)} {
    }

    /* 
     * unchecked constructor: wraps around modulo 2^50
     * if argument overflows Fixint (50 bits)
     */
    explicit inline constexpr Fixint(int64_t i) noexcept
    /**/ : T{tag(i)} {
    }

    /*
     * checked constructor: throws std::overflow_error
     * if argument overflows Fixint (50 bits)
     */
    explicit inline Fixint(int64_t i, check_overflow_t chk) /* throw(std::overflow_error) */
        /**/ : T{tag(i, chk)} {
    }

    /*
    inline constexpr Fixint(const Fixint & other) = default;
    inline constexpr Fixint & operator=(const Fixint & other) = default;
    inline ~Fixint() = default;
    */
    
    inline constexpr int64_t val() const noexcept {
        return untag(bits);
    }

    inline constexpr type_id type() const noexcept {
        return fixint_id;
    }

    enum {
        static_type = fixint_id,
    };

    /* wraps around modulo 2^50: Fixint only holds 50 bits */
    inline constexpr Fixint & operator=(int64_t i) noexcept {
        return (*this) = Fixint{i};
    }

    /* less than */
    inline constexpr bool operator<(Fixint other) noexcept {
        return (int64_t(bits) << tag_nbits)
            < (int64_t(other.bits) << tag_nbits);
    }
    
    /* pre-increment */
    inline constexpr Fixint & operator++() noexcept {
        bits = (bits + 1) | impl::fixint_tag;
        return *this;
    }

    /* post-increment */
    inline constexpr Fixint operator++(int) noexcept {
        Fixint ret = *this;
        bits = (bits + 1) | impl::fixint_tag;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Fixint & operator--() noexcept {
        bits = (bits - 1) | impl::fixint_tag;
        return *this;
    }

    /* post-decrement */
    inline constexpr Fixint operator--(int) noexcept {
        Fixint ret = *this;
        bits = (bits - 1) | impl::fixint_tag;
        return ret;
    }

    /* identity */
    inline constexpr Fixint & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Fixint operator-() noexcept {
        return Fixint{-int64_t(bits)}; // exploit wraparound
    }

    /* boolean negate */
    inline constexpr Fixint operator!() noexcept {
        return Fixint{bits == impl::fixint_tag};
    }

    /* add */
    inline constexpr Fixint & operator+=(Fixint other) noexcept {
        bits = (bits + other.bits) | impl::fixint_tag;
        return *this;
    }

    inline constexpr Fixint & operator+=(int64_t other) noexcept {
        bits = (bits + other) | impl::fixint_tag;
        return *this;
    }

    /* subtract */
    inline constexpr Fixint & operator-=(Fixint other) noexcept {
        bits = (bits - other.bits) | impl::fixint_tag;
        return *this;
    }

    inline constexpr Fixint & operator-=(int64_t other) noexcept {
        bits = (bits - other) | impl::fixint_tag;
        return *this;
    }

    /* multiply */
    inline constexpr Fixint & operator*=(Fixint other) noexcept {
        // no need to untag(bits)
        int64_t i = int64_t(bits), j = untag(other.bits);
        bits = uint64_t(i * j) | impl::fixint_tag;
        return *this;
    }

    inline constexpr Fixint & operator*=(int64_t other) noexcept {
        // no need to untag(bits)
        int64_t i = int64_t(bits), j = other;
        bits = uint64_t(i * j) | impl::fixint_tag;
        return *this;
    }

    /* divide */
    inline constexpr Fixint & operator/=(Fixint other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i / j) | impl::fixint_tag;
        return *this;
    }

    inline constexpr Fixint & operator/=(int64_t other) noexcept {
        int64_t i = untag(bits), j = other;
        bits = uint64_t(i / j) | impl::fixint_tag;
        return *this;
    }

    /* modulus */
    inline constexpr Fixint & operator%=(Fixint other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i % j) | impl::fixint_tag;
        return *this;
    }

    inline constexpr Fixint & operator%=(int64_t other) noexcept {
        int64_t i = untag(bits), j = other;
        bits = uint64_t(i % j) | impl::fixint_tag;
        return *this;
    }

    /* bitwise complement */
    inline constexpr Fixint operator~() noexcept {
        return Fixint{~int64_t(bits)}; // exploit wraparound
    }

    /* bitwise and */
    inline constexpr Fixint & operator&=(Fixint other) noexcept {
        bits = (bits & other.bits) | impl::fixint_tag;
        return *this;
    }

    inline constexpr Fixint & operator&=(int64_t other) noexcept {
        bits = (bits & other) | impl::fixint_tag;
        return *this;
    }

    /* bitwise or */
    inline constexpr Fixint & operator|=(Fixint other) noexcept {
        bits = (bits | other.bits) | impl::fixint_tag;
        return *this;
    }

    inline constexpr Fixint & operator|=(int64_t other) noexcept {
        bits = (bits | other) | impl::fixint_tag;
        return *this;
    }

    /* bitwise xor */
    inline constexpr Fixint & operator^=(Fixint other) noexcept {
        bits = (bits ^ other.bits) | impl::fixint_tag;
        return *this;
    }

    inline constexpr Fixint & operator^=(int64_t other) noexcept {
        bits = (bits ^ other) | impl::fixint_tag;
        return *this;
    }

    /* bitwise lshift */
    inline constexpr Fixint & operator<<=(uint8_t count) noexcept {
        bits = (bits << count) | impl::fixint_tag;
        return *this;
    }

    /* bitwise rshift */
    inline constexpr Fixint & operator>>=(uint8_t count) noexcept {
        int64_t i = untag(bits);
        // shift separately from the shift performed by untag() above,
        // to avoid undefined behaviour if count >= 50
        i >>= count;
        bits = uint64_t(i) | impl::fixint_tag;
        return *this;
    }
};


/* op(Fixint, Fixint) */

inline constexpr bool operator>(Fixint a, Fixint b) noexcept {
    return b < a;
}

inline constexpr bool operator<=(Fixint a, Fixint b) noexcept {
    return !(b < a);
}

inline constexpr bool operator>=(Fixint a, Fixint b) noexcept {
    return !(a < b);
}



inline constexpr Fixint operator+(Fixint a, Fixint b) noexcept {
    return a += b;
}

inline constexpr Fixint operator-(Fixint a, Fixint b) noexcept {
    return a -= b;
}

inline constexpr Fixint operator*(Fixint a, Fixint b) noexcept {
    return a *= b;
}

inline constexpr Fixint operator/(Fixint a, Fixint b) noexcept {
    return a /= b;
}

inline constexpr Fixint operator%(Fixint a, Fixint b) noexcept {
    return a %= b;
}



inline constexpr Fixint operator&(Fixint a, Fixint b) noexcept {
    return a &= b;
}

inline constexpr Fixint operator|(Fixint a, Fixint b) noexcept {
    return a |= b;
}

inline constexpr Fixint operator^(Fixint a, Fixint b) noexcept {
    return a ^= b;
}

inline constexpr Fixint operator<<(Fixint a, uint8_t b) noexcept {
    return a <<= b;
}

inline constexpr Fixint operator>>(Fixint a, uint8_t b) noexcept {
    return a >>= b;
}



/* op(Fixint, int64_t) */

// correct also if a overflows Fixint
inline constexpr bool operator<(Fixint a, int64_t b) noexcept {
    return a.val() < b;
}

// correct also if a overflows Fixint
inline constexpr bool operator>(Fixint a, int64_t b) noexcept {
    return a.val() > b;
}

// correct also if a overflows Fixint
inline constexpr bool operator<=(Fixint a, int64_t b) noexcept {
    return a.val() <= b;
}

// correct also if a overflows Fixint
inline constexpr bool operator>=(Fixint a, int64_t b) noexcept {
    return a.val() >= b;
}


inline constexpr Fixint operator+(Fixint a, int64_t b) noexcept {
    return a += b;
}

inline constexpr Fixint operator-(Fixint a, int64_t b) noexcept {
    return a -= b;
}

inline constexpr Fixint operator*(Fixint a, int64_t b) noexcept {
    return a *= b;
}

inline constexpr Fixint operator/(Fixint a, int64_t b) noexcept {
    return a /= b;
}

inline constexpr Fixint operator%(Fixint a, int64_t b) noexcept {
    return a %= b;
}



inline constexpr Fixint operator&(Fixint a, int64_t b) noexcept {
    return a &= b;
}

inline constexpr Fixint operator|(Fixint a, int64_t b) noexcept {
    return a |= b;
}

inline constexpr Fixint operator^(Fixint a, int64_t b) noexcept {
    return a ^= b;
}




/* op(int64_t, Fixint) */

// correct also if a overflows Fixint
inline constexpr bool operator<(int64_t a, Fixint b) noexcept {
    return a < b.val();
}

// correct also if a overflows Fixint
inline constexpr bool operator>(int64_t a, Fixint b) noexcept {
    return a > b.val();
}

// correct also if a overflows Fixint
inline constexpr bool operator<=(int64_t a, Fixint b) noexcept {
    return a <= b.val();
}

// correct also if a overflows Fixint
inline constexpr bool operator>=(int64_t a, Fixint b) noexcept {
    return a >= b.val();
}


inline constexpr Fixint operator+(int64_t a, Fixint b) noexcept {
    return b += a;
}

inline constexpr Fixint operator-(int64_t a, Fixint b) noexcept {
    return Fixint{a - int64_t(b.debug_bits())};
}

inline constexpr Fixint operator*(int64_t a, Fixint b) noexcept {
    return b *= a;
}

inline constexpr Fixint operator/(int64_t a, Fixint b) noexcept {
    return Fixint{a / b.val()};
}

inline constexpr Fixint operator%(int64_t a, Fixint b) noexcept {
    return Fixint{a % b.val()};
}



inline constexpr Fixint operator&(int64_t a, Fixint b) noexcept {
    return b &= a;
}

inline constexpr Fixint operator|(int64_t a, Fixint b) noexcept {
    return b |= a;
}

inline constexpr Fixint operator^(int64_t a, Fixint b) noexcept {
    return b ^= a;
}


constexpr Fixint fixint_max{ 0x1ffffffffffffll};
constexpr Fixint fixint_min{-0x2000000000000ll};

#endif // CRYSP_FIXINT_HPP
