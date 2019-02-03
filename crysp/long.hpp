#ifndef CRYSP_LONG_HPP
#define CRYSP_LONG_HPP

#include "t.hpp"
#include "long.hpp"
#include "int.hpp"

CRYSP_NS_START

/**
 * 50-bit signed integer.
 * operations on Long are wrapping, i.e. any overflow is truncated modulo 50 bits,
 * except methods with a check_overflow_t argument, which throw an exception on overflow.
 */
class Long : public T {
private:
    friend class T;
    template<class To> friend bool is(T arg);

    // needed by friend is()
    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (~bits >> payload_nbits) == 0;
    }

    enum {
        tag_nbits = 14,
        payload_nbits = 50,
    };
    
    /*
     * int64_t -> Long conversion, modulo 2^50:
     * wraps around if argument overflows Long
     */
    static inline constexpr uint64_t tag(int64_t i) noexcept {
        return uint64_t(i) | impl::long_tag;
    }

    /*
     * checked int64_t -> Long conversion. throws std::overflow_error
     * if argument overflows Long (50 bits)
    */
    static inline uint64_t tag(int64_t i, check_overflow_t) /* throw(std::overflow_error) */ {
        uint32_t hi = uint64_t(i) >> payload_nbits;
        if (hi != 0 && hi != 0x3FFF) {
            impl::throw_overflow_error("Long");
        }
        return uint64_t(i) | impl::long_tag;
    }

    static inline constexpr int64_t untag(uint64_t bits) noexcept {
        return int64_t(bits << tag_nbits) >> tag_nbits;
    }

public:
    inline constexpr Long() noexcept
    /**/: T{uint64_t(impl::long_tag)} {
    }

    /* 
     * unchecked constructor: wraps around modulo 2^50
     * if argument overflows Long (50 bits)
     */
    explicit inline constexpr Long(int64_t i) noexcept
    /**/: T{tag(i)} {
    }

    /*
     * checked constructor: throws std::overflow_error
     * if argument overflows Long (50 bits)
     */
    explicit inline Long(int64_t i, check_overflow_t chk) /* throw(std::overflow_error) */
        : T{tag(i, chk)} {
    }

    /*
     * convert Int (32 bits) to Long (50 bits)
     */
    explicit inline constexpr Long(Int i) noexcept
        : T{tag(i.val())} {
    }

    /*
    inline constexpr Long(const Long & other) = default;
    inline constexpr Long & operator=(const Long & other) = default;
    inline ~Long() = default;
    */
    
    inline constexpr int64_t val() const noexcept {
        return untag(bits);
    }

    static inline constexpr Type type() noexcept {
        return Type{type::long_id};
    }

    static inline constexpr type::id type_id() noexcept {
        return type::long_id;
    }

    enum {
          static_type_id = type::long_id,
    };

    // return number of written bytes
    int print(FILE *out) const;

    /* wraps around modulo 2^50: Long only holds 50 bits */
    inline constexpr Long & operator=(int64_t i) noexcept {
        return (*this) = Long{i};
    }

    /* equal */
    using T::operator==;
    
    inline constexpr bool operator==(int32_t other) noexcept {
        return (int64_t(bits) << tag_nbits) ==
            (int64_t(other) << tag_nbits);
    }

    /* less than */
    inline constexpr bool operator<(Long other) noexcept {
        return (int64_t(bits) << tag_nbits)
            < (int64_t(other.bits) << tag_nbits);
    }

    inline constexpr bool operator<(int32_t other) noexcept {
        return (int64_t(bits) << tag_nbits) <
            (int64_t(other) << tag_nbits);
    }

    inline constexpr bool operator>(int32_t other) noexcept {
        return (int64_t(bits) << tag_nbits) >
            (int64_t(other) << tag_nbits);
    }

    /* pre-increment */
    inline constexpr Long & operator++() noexcept {
        bits = (bits + 1) | impl::long_tag;
        return *this;
    }

    /* post-increment */
    inline constexpr Long operator++(int) noexcept {
        Long ret = *this;
        bits = (bits + 1) | impl::long_tag;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Long & operator--() noexcept {
        bits = (bits - 1) | impl::long_tag;
        return *this;
    }

    /* post-decrement */
    inline constexpr Long operator--(int) noexcept {
        Long ret = *this;
        bits = (bits - 1) | impl::long_tag;
        return ret;
    }

    /* identity */
    inline constexpr Long & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Long operator-() noexcept {
        return Long{-int64_t(bits)}; // exploit wraparound
    }

    /* boolean negate */
    inline constexpr Long operator!() noexcept {
        return Long{bits == impl::long_tag};
    }

    /* add */
    inline constexpr Long & operator+=(Long other) noexcept {
        bits = (bits + other.bits) | impl::long_tag;
        return *this;
    }

    inline constexpr Long & operator+=(int64_t other) noexcept {
        bits = (bits + other) | impl::long_tag;
        return *this;
    }

    /* subtract */
    inline constexpr Long & operator-=(Long other) noexcept {
        bits = (bits - other.bits) | impl::long_tag;
        return *this;
    }

    inline constexpr Long & operator-=(int64_t other) noexcept {
        bits = (bits - other) | impl::long_tag;
        return *this;
    }

    /* multiply */
    inline constexpr Long & operator*=(Long other) noexcept {
        // no need to untag(bits)
        int64_t i = int64_t(bits), j = int64_t(other.bits);
        bits = uint64_t(i * j) | impl::long_tag;
        return *this;
    }

    inline constexpr Long & operator*=(int64_t other) noexcept {
        // no need to untag(bits)
        int64_t i = int64_t(bits), j = other;
        bits = uint64_t(i * j) | impl::long_tag;
        return *this;
    }

    /* divide */
    inline constexpr Long & operator/=(Long other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i / j) | impl::long_tag;
        return *this;
    }

    inline constexpr Long & operator/=(int64_t other) noexcept {
        int64_t i = untag(bits), j = other;
        bits = uint64_t(i / j) | impl::long_tag;
        return *this;
    }

    /* modulus */
    inline constexpr Long & operator%=(Long other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i % j) | impl::long_tag;
        return *this;
    }

    inline constexpr Long & operator%=(int64_t other) noexcept {
        int64_t i = untag(bits), j = other;
        bits = uint64_t(i % j) | impl::long_tag;
        return *this;
    }

    /* bitwise complement */
    inline constexpr Long operator~() noexcept {
        return Long{~int64_t(bits)}; // exploit wraparound
    }

    /* bitwise and */
    inline constexpr Long & operator&=(Long other) noexcept {
        bits &= other.bits; // preserves tag
        return *this;
    }

    inline constexpr Long & operator&=(int64_t other) noexcept {
        bits &= uint64_t(other) | impl::long_tag;
        return *this;
    }

    /* bitwise or */
    inline constexpr Long & operator|=(Long other) noexcept {
        bits |= other.bits; // preserves tag
        return *this;
    }

    inline constexpr Long & operator|=(int64_t other) noexcept {
        bits |= uint64_t(other); // preserves tag
        return *this;
    }

    /* bitwise xor */
    inline constexpr Long & operator^=(Long other) noexcept {
        bits = (bits ^ other.bits) | impl::long_tag;
        return *this;
    }

    inline constexpr Long & operator^=(int64_t other) noexcept {
        bits = (bits ^ other) | impl::long_tag;
        return *this;
    }

    /* bitwise lshift */
    inline constexpr Long & operator<<=(uint8_t count) noexcept {
        bits = (bits << count) | impl::long_tag;
        return *this;
    }

    /* bitwise rshift */
    inline constexpr Long & operator>>=(uint8_t count) noexcept {
        int64_t i = untag(bits);
        // shift separately from the shift performed by untag() above,
        // to avoid undefined behaviour if count >= 50
        i >>= count;
        bits = uint64_t(i) | impl::long_tag;
        return *this;
    }
};


/* op(Long, Long) */

inline constexpr bool operator>(Long a, Long b) noexcept {
    return b < a;
}

inline constexpr bool operator<=(Long a, Long b) noexcept {
    return !(b < a);
}

inline constexpr bool operator>=(Long a, Long b) noexcept {
    return !(a < b);
}


inline constexpr Long operator+(Long a, Long b) noexcept {
    return a += b;
}

inline constexpr Long operator-(Long a, Long b) noexcept {
    return a -= b;
}

inline constexpr Long operator*(Long a, Long b) noexcept {
    return a *= b;
}

inline constexpr Long operator/(Long a, Long b) noexcept {
    return a /= b;
}

inline constexpr Long operator%(Long a, Long b) noexcept {
    return a %= b;
}



inline constexpr Long operator&(Long a, Long b) noexcept {
    return a &= b;
}

inline constexpr Long operator|(Long a, Long b) noexcept {
    return a |= b;
}

inline constexpr Long operator^(Long a, Long b) noexcept {
    return a ^= b;
}

inline constexpr Long operator<<(Long a, uint8_t b) noexcept {
    return a <<= b;
}

inline constexpr Long operator>>(Long a, uint8_t b) noexcept {
    return a >>= b;
}


/* op(Long, int64_t) */

// correct also if b overflows Long
inline constexpr bool operator==(Long a, int64_t b) noexcept {
    return a.val() == b;
}

// correct also if b overflows Long
inline constexpr bool operator!=(Long a, int64_t b) noexcept {
    return a.val() != b;
}

// correct also if b overflows Long
inline constexpr bool operator<(Long a, int64_t b) noexcept {
    return a.val() < b;
}

// correct also if b overflows Long
inline constexpr bool operator>(Long a, int64_t b) noexcept {
    return a.val() > b;
}

// correct also if b overflows Long
inline constexpr bool operator<=(Long a, int64_t b) noexcept {
    return a.val() <= b;
}

// correct also if b overflows Long
inline constexpr bool operator>=(Long a, int64_t b) noexcept {
    return a.val() >= b;
}


inline constexpr Long operator+(Long a, int64_t b) noexcept {
    return a += b;
}

inline constexpr Long operator-(Long a, int64_t b) noexcept {
    return a -= b;
}

inline constexpr Long operator*(Long a, int64_t b) noexcept {
    return a *= b;
}

inline constexpr Long operator/(Long a, int64_t b) noexcept {
    return a /= b;
}

inline constexpr Long operator%(Long a, int64_t b) noexcept {
    return a %= b;
}



inline constexpr Long operator&(Long a, int64_t b) noexcept {
    return a &= b;
}

inline constexpr Long operator|(Long a, int64_t b) noexcept {
    return a |= b;
}

inline constexpr Long operator^(Long a, int64_t b) noexcept {
    return a ^= b;
}




/* op(int64_t, Long) */

// correct also if a overflows Long
inline constexpr bool operator==(int64_t a, Long b) noexcept {
    return a == b.val();
}

// correct also if a overflows Long
inline constexpr bool operator!=(int64_t a, Long b) noexcept {
    return a != b.val();
}

// correct also if a overflows Long
inline constexpr bool operator<(int64_t a, Long b) noexcept {
    return a < b.val();
}

// correct also if a overflows Long
inline constexpr bool operator>(int64_t a, Long b) noexcept {
    return a > b.val();
}

// correct also if a overflows Long
inline constexpr bool operator<=(int64_t a, Long b) noexcept {
    return a <= b.val();
}

// correct also if a overflows Long
inline constexpr bool operator>=(int64_t a, Long b) noexcept {
    return a >= b.val();
}


inline constexpr Long operator+(int64_t a, Long b) noexcept {
    return b += a;
}

inline constexpr Long operator-(int64_t a, Long b) noexcept {
    return Long{a - int64_t(b.debug_bits())};
}

inline constexpr Long operator*(int64_t a, Long b) noexcept {
    return b *= a;
}

inline constexpr Long operator/(int64_t a, Long b) noexcept {
    return Long{a / b.val()};
}

inline constexpr Long operator%(int64_t a, Long b) noexcept {
    return Long{a % b.val()};
}



inline constexpr Long operator&(int64_t a, Long b) noexcept {
    return b &= a;
}

inline constexpr Long operator|(int64_t a, Long b) noexcept {
    return b |= a;
}

inline constexpr Long operator^(int64_t a, Long b) noexcept {
    return b ^= a;
}



/* op(Long, int32_t) */

inline constexpr bool operator!=(Long a, int32_t b) noexcept {
    return !(a == b);
}

inline constexpr bool operator<=(Long a, int32_t b) noexcept {
    return !(a > b);
}

inline constexpr bool operator>=(Long a, int32_t b) noexcept {
    return !(a < b);
}


/* op(int32_t, Long) */

inline constexpr bool operator==(int32_t a, Long b) noexcept {
    return b == a;
}

inline constexpr bool operator!=(int32_t a, Long b) noexcept {
    return !(b == a);
}

inline constexpr bool operator<=(int32_t a, Long b) noexcept {
    return b > a;
}

inline constexpr bool operator>=(int32_t a, Long b) noexcept {
    return b < a;
}


constexpr Long long_max{ 0x1ffffffffffffll};
constexpr Long long_min{-0x2000000000000ll};

CRYSP_NS_END

#endif // CRYSP_LONG_HPP
