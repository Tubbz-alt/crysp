#ifndef CRYSP_INT_HPP
#define CRYSP_INT_HPP

#include "t.hpp"
#include "short.hpp"

/**
 * 50-bit signed integer.
 * operations on Int are wrapping, i.e. any overflow is truncated modulo 50 bits,
 * except methods with a check_overflow_t argument, which throw an exception on overflow.
 */
class Int : public T {
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
     * int64_t -> Int conversion, modulo 2^50:
     * wraps around if argument overflows Int
     */
    static inline constexpr uint64_t tag(int64_t i) noexcept {
        return uint64_t(i) | impl::int_tag;
    }

    /*
     * checked int64_t -> Int conversion. throws std::overflow_error
     * if argument overflows Int (50 bits)
    */
    static inline uint64_t tag(int64_t i, check_overflow_t) /* throw(std::overflow_error) */ {
        uint32_t hi = uint64_t(i) >> payload_nbits;
        if (hi != 0 && hi != 0x3FFF) {
            impl::throw_overflow_error("Int");
        }
        return uint64_t(i) | impl::int_tag;
    }

    static inline constexpr int64_t untag(uint64_t bits) noexcept {
        return int64_t(bits << tag_nbits) >> tag_nbits;
    }

public:
    inline constexpr Int() noexcept
    /**/: T{uint64_t(impl::int_tag)} {
    }

    /* 
     * unchecked constructor: wraps around modulo 2^50
     * if argument overflows Int (50 bits)
     */
    explicit inline constexpr Int(int64_t i) noexcept
    /**/: T{tag(i)} {
    }

    /*
     * checked constructor: throws std::overflow_error
     * if argument overflows Int (50 bits)
     */
    explicit inline Int(int64_t i, check_overflow_t chk) /* throw(std::overflow_error) */
        : T{tag(i, chk)} {
    }

    /*
     * convert Short (32 bits) to Int (50 bits)
     */
    explicit inline constexpr Int(Short i) noexcept
        : T{tag(i.val())} {
    }

    /*
    inline constexpr Int(const Int & other) = default;
    inline constexpr Int & operator=(const Int & other) = default;
    inline ~Int() = default;
    */
    
    inline constexpr int64_t val() const noexcept {
        return untag(bits);
    }

    // defined in type.hpp
    inline constexpr Type type() const noexcept;

    inline constexpr type::id type_id() const noexcept {
        return type::int_id;
    }

    enum {
          static_type_id = type::int_id,
    };

    // return number of written bytes
    int print(FILE *out) const;

    /* wraps around modulo 2^50: Int only holds 50 bits */
    inline constexpr Int & operator=(int64_t i) noexcept {
        return (*this) = Int{i};
    }

    /* less than */
    inline constexpr bool operator<(Int other) noexcept {
        return (int64_t(bits) << tag_nbits)
            < (int64_t(other.bits) << tag_nbits);
    }
    
    /* pre-increment */
    inline constexpr Int & operator++() noexcept {
        bits = (bits + 1) | impl::int_tag;
        return *this;
    }

    /* post-increment */
    inline constexpr Int operator++(int) noexcept {
        Int ret = *this;
        bits = (bits + 1) | impl::int_tag;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Int & operator--() noexcept {
        bits = (bits - 1) | impl::int_tag;
        return *this;
    }

    /* post-decrement */
    inline constexpr Int operator--(int) noexcept {
        Int ret = *this;
        bits = (bits - 1) | impl::int_tag;
        return ret;
    }

    /* identity */
    inline constexpr Int & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Int operator-() noexcept {
        return Int{-int64_t(bits)}; // exploit wraparound
    }

    /* boolean negate */
    inline constexpr Int operator!() noexcept {
        return Int{bits == impl::int_tag};
    }

    /* add */
    inline constexpr Int & operator+=(Int other) noexcept {
        bits = (bits + other.bits) | impl::int_tag;
        return *this;
    }

    inline constexpr Int & operator+=(int64_t other) noexcept {
        bits = (bits + other) | impl::int_tag;
        return *this;
    }

    /* subtract */
    inline constexpr Int & operator-=(Int other) noexcept {
        bits = (bits - other.bits) | impl::int_tag;
        return *this;
    }

    inline constexpr Int & operator-=(int64_t other) noexcept {
        bits = (bits - other) | impl::int_tag;
        return *this;
    }

    /* multiply */
    inline constexpr Int & operator*=(Int other) noexcept {
        // no need to untag(bits)
        int64_t i = int64_t(bits), j = untag(other.bits);
        bits = uint64_t(i * j) | impl::int_tag;
        return *this;
    }

    inline constexpr Int & operator*=(int64_t other) noexcept {
        // no need to untag(bits)
        int64_t i = int64_t(bits), j = other;
        bits = uint64_t(i * j) | impl::int_tag;
        return *this;
    }

    /* divide */
    inline constexpr Int & operator/=(Int other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i / j) | impl::int_tag;
        return *this;
    }

    inline constexpr Int & operator/=(int64_t other) noexcept {
        int64_t i = untag(bits), j = other;
        bits = uint64_t(i / j) | impl::int_tag;
        return *this;
    }

    /* modulus */
    inline constexpr Int & operator%=(Int other) noexcept {
        int64_t i = untag(bits), j = untag(other.bits);
        bits = uint64_t(i % j) | impl::int_tag;
        return *this;
    }

    inline constexpr Int & operator%=(int64_t other) noexcept {
        int64_t i = untag(bits), j = other;
        bits = uint64_t(i % j) | impl::int_tag;
        return *this;
    }

    /* bitwise complement */
    inline constexpr Int operator~() noexcept {
        return Int{~int64_t(bits)}; // exploit wraparound
    }

    /* bitwise and */
    inline constexpr Int & operator&=(Int other) noexcept {
        bits = (bits & other.bits) | impl::int_tag;
        return *this;
    }

    inline constexpr Int & operator&=(int64_t other) noexcept {
        bits = (bits & other) | impl::int_tag;
        return *this;
    }

    /* bitwise or */
    inline constexpr Int & operator|=(Int other) noexcept {
        bits = (bits | other.bits) | impl::int_tag;
        return *this;
    }

    inline constexpr Int & operator|=(int64_t other) noexcept {
        bits = (bits | other) | impl::int_tag;
        return *this;
    }

    /* bitwise xor */
    inline constexpr Int & operator^=(Int other) noexcept {
        bits = (bits ^ other.bits) | impl::int_tag;
        return *this;
    }

    inline constexpr Int & operator^=(int64_t other) noexcept {
        bits = (bits ^ other) | impl::int_tag;
        return *this;
    }

    /* bitwise lshift */
    inline constexpr Int & operator<<=(uint8_t count) noexcept {
        bits = (bits << count) | impl::int_tag;
        return *this;
    }

    /* bitwise rshift */
    inline constexpr Int & operator>>=(uint8_t count) noexcept {
        int64_t i = untag(bits);
        // shift separately from the shift performed by untag() above,
        // to avoid undefined behaviour if count >= 50
        i >>= count;
        bits = uint64_t(i) | impl::int_tag;
        return *this;
    }
};


/* op(Int, Int) */

inline constexpr bool operator>(Int a, Int b) noexcept {
    return b < a;
}

inline constexpr bool operator<=(Int a, Int b) noexcept {
    return !(b < a);
}

inline constexpr bool operator>=(Int a, Int b) noexcept {
    return !(a < b);
}


inline constexpr Int operator+(Int a, Int b) noexcept {
    return a += b;
}

inline constexpr Int operator-(Int a, Int b) noexcept {
    return a -= b;
}

inline constexpr Int operator*(Int a, Int b) noexcept {
    return a *= b;
}

inline constexpr Int operator/(Int a, Int b) noexcept {
    return a /= b;
}

inline constexpr Int operator%(Int a, Int b) noexcept {
    return a %= b;
}



inline constexpr Int operator&(Int a, Int b) noexcept {
    return a &= b;
}

inline constexpr Int operator|(Int a, Int b) noexcept {
    return a |= b;
}

inline constexpr Int operator^(Int a, Int b) noexcept {
    return a ^= b;
}

inline constexpr Int operator<<(Int a, uint8_t b) noexcept {
    return a <<= b;
}

inline constexpr Int operator>>(Int a, uint8_t b) noexcept {
    return a >>= b;
}



/* op(Int, int64_t) */

// correct also if a overflows Int
inline constexpr bool operator<(Int a, int64_t b) noexcept {
    return a.val() < b;
}

// correct also if a overflows Int
inline constexpr bool operator>(Int a, int64_t b) noexcept {
    return a.val() > b;
}

// correct also if a overflows Int
inline constexpr bool operator<=(Int a, int64_t b) noexcept {
    return a.val() <= b;
}

// correct also if a overflows Int
inline constexpr bool operator>=(Int a, int64_t b) noexcept {
    return a.val() >= b;
}


inline constexpr Int operator+(Int a, int64_t b) noexcept {
    return a += b;
}

inline constexpr Int operator-(Int a, int64_t b) noexcept {
    return a -= b;
}

inline constexpr Int operator*(Int a, int64_t b) noexcept {
    return a *= b;
}

inline constexpr Int operator/(Int a, int64_t b) noexcept {
    return a /= b;
}

inline constexpr Int operator%(Int a, int64_t b) noexcept {
    return a %= b;
}



inline constexpr Int operator&(Int a, int64_t b) noexcept {
    return a &= b;
}

inline constexpr Int operator|(Int a, int64_t b) noexcept {
    return a |= b;
}

inline constexpr Int operator^(Int a, int64_t b) noexcept {
    return a ^= b;
}




/* op(int64_t, Int) */

// correct also if a overflows Int
inline constexpr bool operator<(int64_t a, Int b) noexcept {
    return a < b.val();
}

// correct also if a overflows Int
inline constexpr bool operator>(int64_t a, Int b) noexcept {
    return a > b.val();
}

// correct also if a overflows Int
inline constexpr bool operator<=(int64_t a, Int b) noexcept {
    return a <= b.val();
}

// correct also if a overflows Int
inline constexpr bool operator>=(int64_t a, Int b) noexcept {
    return a >= b.val();
}


inline constexpr Int operator+(int64_t a, Int b) noexcept {
    return b += a;
}

inline constexpr Int operator-(int64_t a, Int b) noexcept {
    return Int{a - int64_t(b.debug_bits())};
}

inline constexpr Int operator*(int64_t a, Int b) noexcept {
    return b *= a;
}

inline constexpr Int operator/(int64_t a, Int b) noexcept {
    return Int{a / b.val()};
}

inline constexpr Int operator%(int64_t a, Int b) noexcept {
    return Int{a % b.val()};
}



inline constexpr Int operator&(int64_t a, Int b) noexcept {
    return b &= a;
}

inline constexpr Int operator|(int64_t a, Int b) noexcept {
    return b |= a;
}

inline constexpr Int operator^(int64_t a, Int b) noexcept {
    return b ^= a;
}


constexpr Int int_max{ 0x1ffffffffffffll};
constexpr Int int_min{-0x2000000000000ll};

#endif // CRYSP_INT_HPP
