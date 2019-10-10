#ifndef CRYSP_INT_HPP
#define CRYSP_INT_HPP

#include "t.hpp"
#include "type.hpp"

CRYSP_NS_START

// architecture-dependent optimizations
#define CRYSP_INT_OBJ_INPLACE
#define CRYSP_INT_REF_INPLACE


/**
 * 32-bit signed integer.
 * operations on Int are wrapping, i.e. any overflow is truncated modulo 32 bits,
 * except methods with a check_overflow_t argument, which throw an exception on overflow.
 */
class Int : public T {
private:
    friend class T;
    template<class To> friend bool is(T arg);

    friend constexpr Int operator&(Int a, Int b) noexcept;
    friend constexpr Int operator|(Int a, Int b) noexcept;
    friend constexpr Int operator|(Int a, int32_t b) noexcept;
    friend constexpr Int operator|(int32_t a, Int b) noexcept;

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return bits >> 48 == impl::int_tag >> 48;
    }

    struct bits_constructor{};

    inline constexpr Int(uint64_t bits, bits_constructor) noexcept
	: T{bits} {
    }

public:
    inline constexpr Int() noexcept
    /**/ : T{int32_t(0), uint32_t(impl::int_tag >> 32)} {
    }

    explicit inline constexpr Int(int32_t i) noexcept
        : T{int32_t(i), uint32_t(impl::int_tag >> 32)} {
    }

    /*
    inline constexpr Int(const Int & other) = default;
    inline constexpr Int & operator=(const Int & other) = default;
    inline ~Int() = default;
    */
    
    inline constexpr int32_t val() const noexcept {
        return i;
    }

    static inline constexpr Type type() noexcept {
        return Type{type::int_id};
    }
    
    static inline constexpr type::id type_id() noexcept {
        return type::int_id;
    }

    enum {
        static_type_id = type::int_id,
    };

    // return number of written bytes
    int print(FILE *out) const;

    /* identity */
    inline constexpr Int & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Int operator-() noexcept {
        return Int{-i};
    }

    /* boolean negate */
    inline constexpr Int operator!() noexcept {
        return Int{int32_t(!i)};
    }
    
    /* bitwise complement */
    inline constexpr Int operator~() noexcept {
        return Int{~i};
    }

#ifdef CRYSP_INT_REF_INPLACE
    /* assign */
    inline constexpr Int & operator=(int32_t other) noexcept {
        i = other;
        return *this;
    }

    /* pre-increment */
    inline constexpr Int & operator++() noexcept {
        ++i;
        return *this;
    }

    /* post-increment */
    inline constexpr Int operator++(int) noexcept {
        Int ret = *this;
        ++i;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Int & operator--() noexcept {
        --i;
        return *this;
    }

    /* post-decrement */
    inline constexpr Int operator--(int) noexcept {
        Int ret = *this;
        --i;
        return ret;
    }

    /* add */
    inline constexpr Int & operator+=(Int other) noexcept {
        i += other.i;
        return *this;
    }

    inline constexpr Int & operator+=(int32_t other) noexcept {
        i += other;
        return *this;
    }

    /* subtract */
    inline constexpr Int & operator-=(Int other) noexcept {
        i -= other.i;
        return *this;
    }

    inline constexpr Int & operator-=(int32_t other) noexcept {
        i -= other;
        return *this;
    }

    /* multiply */
    inline constexpr Int & operator*=(Int other) noexcept {
        i *= other.i;
        return *this;
    }

    inline constexpr Int & operator*=(int32_t other) noexcept {
        i *= other;
        return *this;
    }

    /* divide */
    inline constexpr Int & operator/=(Int other) noexcept {
        i /= other.i;
        return *this;
    }

    inline constexpr Int & operator/=(int32_t other) noexcept {
        i /= other;
        return *this;
    }

    /* modulus */
    inline constexpr Int & operator%=(Int other) noexcept {
        i %= other.i;
        return *this;
    }

    inline constexpr Int & operator%=(int32_t other) noexcept {
        i %= other;
        return *this;
    }

    /* bitwise and */
    inline constexpr Int & operator&=(Int other) noexcept {
        // preserves tag
        return *this = Int{bits & other.bits, bits_constructor{}};
    }

    inline constexpr Int & operator&=(int32_t other) noexcept {
        i &= other;
        return *this;
    }

    /* bitwise or */
    inline constexpr Int & operator|=(Int other) noexcept {
        // preserves tag
        return *this = Int{bits | other.bits, bits_constructor{}};
    }

    inline constexpr Int & operator|=(int32_t other) noexcept {
        // preserves tag
        return *this = Int{bits | uint32_t(other), bits_constructor{}};
    }

    /* bitwise xor */
    inline constexpr Int & operator^=(Int other) noexcept {
        i ^= other.i;
        return *this;
    }

    inline constexpr Int & operator^=(int32_t other) noexcept {
        i ^= other;
        return *this;
    }

    /* bitwise lshift */
    inline constexpr Int & operator<<=(uint8_t count) noexcept {
        i <<= count;
        return *this;
    }

    /* bitwise rshift */
    inline constexpr Int & operator>>=(uint8_t count) noexcept {
        i >>= count;
        return *this;
    }
#else // !CRYSP_INT_REF_INPLACE
    /* assign */
    inline constexpr Int & operator=(int32_t i) noexcept {
        return (*this) = Int{i};
    }

    /* pre-increment */
    inline constexpr Int & operator++() noexcept {
        return *this = Int{i + 1};
    }

    /* post-increment */
    inline constexpr Int operator++(int) noexcept {
        Int ret = *this;
        *this = Int{i + 1};
        return ret;
    }

    /* pre-decrement */
    inline constexpr Int & operator--() noexcept {
        return *this = Int{i - 1};
    }

    /* post-decrement */
    inline constexpr Int operator--(int) noexcept {
        Int ret = *this;
        *this = Int{i - 1};
        return ret;
    }

    /* add */
    inline constexpr Int & operator+=(Int other) noexcept {
        return *this = Int{i + other.i};
    }

    inline constexpr Int & operator+=(int32_t other) noexcept {
        return *this = Int{i + other};
    }

    /* subtract */
    inline constexpr Int & operator-=(Int other) noexcept {
        return *this = Int{i - other.i};
    }

    inline constexpr Int & operator-=(int32_t other) noexcept {
        return *this = Int{i - other};
    }

    /* multiply */
    inline constexpr Int & operator*=(Int other) noexcept {
        return *this = Int{i * other.i};
    }

    inline constexpr Int & operator*=(int32_t other) noexcept {
        return *this = Int{i * other};
    }

    /* divide */
    inline constexpr Int & operator/=(Int other) noexcept {
        return *this = Int{i / other.i};
    }

    inline constexpr Int & operator/=(int32_t other) noexcept {
        return *this = Int{i / other};
    }

    /* modulus */
    inline constexpr Int & operator%=(Int other) noexcept {
        return *this = Int{i % other.i};
    }

    inline constexpr Int & operator%=(int32_t other) noexcept {
        return *this = Int{i % other};
    }

    /* bitwise and */
    inline constexpr Int & operator&=(Int other) noexcept {
        // preserves tag
        return *this = Int{bits & other.bits, bits_constructor{}};
    }

    inline constexpr Int & operator&=(int32_t other) noexcept {
        return *this = Int{i & other};
    }

    /* bitwise or */
    inline constexpr Int & operator|=(Int other) noexcept {
        // preserves tag
        return *this = Int{bits | other.bits, bits_constructor{}};
    }

    inline constexpr Int & operator|=(int32_t other) noexcept {
        // preserves tag
        return *this = Int{bits | uint32_t(other), bits_constructor{}};
    }

    /* bitwise xor */
    inline constexpr Int & operator^=(Int other) noexcept {
        return *this = Int{i ^ other.i};
    }

    inline constexpr Int & operator^=(int32_t other) noexcept {
        return *this = Int{i ^ other};
    }

    /* bitwise lshift */
    inline constexpr Int & operator<<=(uint8_t count) noexcept {
        return *this = Int{i << count};
    }

    /* bitwise rshift */
    inline constexpr Int & operator>>=(uint8_t count) noexcept {
        return *this = Int{i >> count};
    }
#endif // CRYSP_INT_REF_INPLACE
};

constexpr Int int_max{int32_t(0x7fffffffl)}, int_min{int32_t(-0x80000000l)};

/* relational operators */
inline constexpr bool operator==(Int a, int32_t b) noexcept {
    return a.val() == b;
}

inline constexpr bool operator==(int32_t a, Int b) noexcept {
    return a == b.val();
}

inline constexpr bool operator!=(Int a, int32_t b) noexcept {
    return a.val() != b;
}

inline constexpr bool operator!=(int32_t a, Int b) noexcept {
    return a != b.val();
}

inline constexpr bool operator<(Int a, Int b) noexcept {
    return a.val() < b.val();
}

inline constexpr bool operator<(Int a, int32_t b) noexcept {
    return a.val() < b;
}

inline constexpr bool operator<(int32_t a, Int b) noexcept {
    return a < b.val();
}

inline constexpr bool operator>(Int a, Int b) noexcept {
    return a.val() > b.val();
}

inline constexpr bool operator>(Int a, int32_t b) noexcept {
    return a.val() > b;
}

inline constexpr bool operator>(int32_t a, Int b) noexcept {
    return a > b.val();
}

inline constexpr bool operator<=(Int a, Int b) noexcept {
    return a.val() <= b.val();
}

inline constexpr bool operator<=(Int a, int32_t b) noexcept {
    return a.val() <= b;
}

inline constexpr bool operator<=(int32_t a, Int b) noexcept {
    return a <= b.val();
}

inline constexpr bool operator>=(Int a, Int b) noexcept {
    return a.val() >= b.val();
}

inline constexpr bool operator>=(Int a, int32_t b) noexcept {
    return a.val() >= b;
}

inline constexpr bool operator>=(int32_t a, Int b) noexcept {
    return a >= b.val();
}

/* arithmetic operators */
#ifdef CRYSP_INT_OBJ_INPLACE
inline constexpr Int operator+(Int a, Int b) noexcept {
    return a += b;
}

inline constexpr Int operator+(Int a, int32_t b) noexcept {
    return a += b;
}

inline constexpr Int operator+(int32_t a, Int b) noexcept {
    return b += a;
}

inline constexpr Int operator-(Int a, Int b) noexcept {
    return a -= b;
}

inline constexpr Int operator-(Int a, int32_t b) noexcept {
    return a -= b;
}

inline constexpr Int operator-(int32_t a, Int b) noexcept {
    return b = a - b.val();
}

inline constexpr Int operator*(Int a, Int b) noexcept {
    return a *= b;
}

inline constexpr Int operator*(Int a, int32_t b) noexcept {
    return a *= b;
}

inline constexpr Int operator*(int32_t a, Int b) noexcept {
    return b *= a;
}

inline constexpr Int operator/(Int a, Int b) noexcept {
    return a /= b;
}

inline constexpr Int operator/(Int a, int32_t b) noexcept {
    return a /= b;
}

inline constexpr Int operator/(int32_t a, Int b) noexcept {
    return b = a / b.val();
}

inline constexpr Int operator%(Int a, Int b) noexcept {
    return a %= b;
}

inline constexpr Int operator%(Int a, int32_t b) noexcept {
    return a %= b;
}

inline constexpr Int operator%(int32_t a, Int b) noexcept {
    return b = a % b.val();
}

inline constexpr Int operator&(Int a, Int b) noexcept {
    return a &= b;
}

inline constexpr Int operator&(Int a, int32_t b) noexcept {
    return a &= b;
}

inline constexpr Int operator&(int32_t a, Int b) noexcept {
    return b &= a;
}

inline constexpr Int operator|(Int a, Int b) noexcept {
    return a |= b;
}

inline constexpr Int operator|(Int a, int32_t b) noexcept {
    return a |= b;
}

inline constexpr Int operator|(int32_t a, Int b) noexcept {
    return b |= a;
}

inline constexpr Int operator^(Int a, Int b) noexcept {
    return a ^= b;
}

inline constexpr Int operator^(Int a, int32_t b) noexcept {
    return a ^= b;
}

inline constexpr Int operator^(int32_t a, Int b) noexcept {
    return b ^= a;
}

inline constexpr Int operator<<(Int a, uint8_t b) noexcept {
    return a <<= b;
}

inline constexpr Int operator>>(Int a, uint8_t b) noexcept {
    return a >>= b;
}

#else // !CRYSP_INT_OBJ_INPLACE
inline constexpr Int operator+(Int a, Int b) noexcept {
    return Int{a.val() + b.val()};
}

inline constexpr Int operator+(Int a, int32_t b) noexcept {
    return Int{a.val() + b};
}

inline constexpr Int operator+(int32_t a, Int b) noexcept {
    return Int{a + b.val()};
}

inline constexpr Int operator-(Int a, Int b) noexcept {
    return Int{a.val() - b.val()};
}

inline constexpr Int operator-(Int a, int32_t b) noexcept {
    return Int{a.val() - b};
}

inline constexpr Int operator-(int32_t a, Int b) noexcept {
    return Int{a - b.val()};
}

inline constexpr Int operator*(Int a, Int b) noexcept {
    return Int{a.val() * b.val()};
}

inline constexpr Int operator*(Int a, int32_t b) noexcept {
    return Int{a.val() * b};
}

inline constexpr Int operator*(int32_t a, Int b) noexcept {
    return Int{a * b.val()};
}

inline constexpr Int operator/(Int a, Int b) noexcept {
    return Int{a.val() / b.val()};
}

inline constexpr Int operator/(Int a, int32_t b) noexcept {
    return Int{a.val() / b};
}

inline constexpr Int operator/(int32_t a, Int b) noexcept {
    return Int{a / b.val()};
}

inline constexpr Int operator%(Int a, Int b) noexcept {
    return Int{a.val() % b.val()};
}

inline constexpr Int operator%(Int a, int32_t b) noexcept {
    return Int{a.val() % b};
}

inline constexpr Int operator%(int32_t a, Int b) noexcept {
    return Int{a % b.val()};
}

inline constexpr Int operator&(Int a, Int b) noexcept {
    return Int{a.debug_bits() & b.debug_bits(), Int::bits_constructor{}};
}

inline constexpr Int operator&(Int a, int32_t b) noexcept {
    return Int{a.val() & b};
}

inline constexpr Int operator&(int32_t a, Int b) noexcept {
    return Int{a & b.val()};
}

inline constexpr Int operator|(Int a, Int b) noexcept {
    return Int{a.debug_bits() | b.debug_bits(), Int::bits_constructor{}};
}

inline constexpr Int operator|(Int a, int32_t b) noexcept {
    return Int{a.debug_bits() | uint32_t(b), Int::bits_constructor{}};
}

inline constexpr Int operator|(int32_t a, Int b) noexcept {
    return Int{uint32_t(a) | b.debug_bits(), Int::bits_constructor{}};
}

inline constexpr Int operator^(Int a, Int b) noexcept {
    return Int{a.val() ^ b.val()};
}

inline constexpr Int operator^(Int a, int32_t b) noexcept {
    return Int{a.val() ^ b};
}

inline constexpr Int operator^(int32_t a, Int b) noexcept {
    return Int{a ^ b.val()};
}

inline constexpr Int operator<<(Int a, uint8_t b) noexcept {
    return Int{a.val() << b};
}

inline constexpr Int operator>>(Int a, uint8_t b) noexcept {
    return Int{a.val() >> b};
}
#endif // CRYSP_INT_OBJ_INPLACE

CRYSP_NS_END

#endif // CRYSP_INT_HPP
