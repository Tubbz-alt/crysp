#ifndef CRYSP_SHORT_HPP
#define CRYSP_SHORT_HPP

#include "t.hpp"
#include "type.hpp"

CRYSP_NS_START

// optimizations
#define CRYSP_SHORT_REF_INPLACE

#if defined(__x86_64__) || defined(__x86_64) || \
    defined(__i386__) || defined(__i386)
# undef CRYSP_SHORT_OBJ_INPLACE
#else
# define CRYSP_SHORT_OBJ_INPLACE
#endif

/**
 * 32-bit signed integer.
 * operations on Short are wrapping, i.e. any overflow is truncated modulo 32 bits,
 * except methods with a check_overflow_t argument, which throw an exception on overflow.
 */
class Short : public T {
private:
    friend class T;
    template<class To> friend bool is(T arg);

    friend constexpr Short operator&(Short a, Short b) noexcept;
    friend constexpr Short operator|(Short a, Short b) noexcept;
    friend constexpr Short operator|(Short a, int32_t b) noexcept;
    friend constexpr Short operator|(int32_t a, Short b) noexcept;

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return bits >> 48 == impl::short_tag >> 48;
    }

    struct bits_constructor{};

    inline constexpr Short(uint64_t bits, bits_constructor) noexcept
	: T{bits} {
    }

public:
    inline constexpr Short() noexcept
    /**/ : T{int32_t(0), uint32_t(impl::short_tag >> 32)} {
    }

    explicit inline constexpr Short(int32_t i) noexcept
        : T{int32_t(i), uint32_t(impl::short_tag >> 32)} {
    }

    /*
    inline constexpr Short(const Short & other) = default;
    inline constexpr Short & operator=(const Short & other) = default;
    inline ~Short() = default;
    */
    
    inline constexpr int32_t val() const noexcept {
        return i;
    }

    static inline constexpr Type type() noexcept {
        return Type{type::short_id};
    }
    
    static inline constexpr type::id type_id() noexcept {
        return type::short_id;
    }

    enum {
        static_type_id = type::short_id,
    };

    // return number of written bytes
    int print(FILE *out) const;

    /* identity */
    inline constexpr Short & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Short operator-() noexcept {
        return Short{-i};
    }

    /* boolean negate */
    inline constexpr Short operator!() noexcept {
        return Short{int32_t(!i)};
    }
    
    /* bitwise complement */
    inline constexpr Short operator~() noexcept {
        return Short{~i};
    }

#ifdef CRYSP_SHORT_REF_INPLACE
    /* assign */
    inline constexpr Short & operator=(int32_t other) noexcept {
        i = other;
        return *this;
    }

    /* pre-increment */
    inline constexpr Short & operator++() noexcept {
        ++i;
        return *this;
    }

    /* post-increment */
    inline constexpr Short operator++(int) noexcept {
        Short ret = *this;
        ++i;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Short & operator--() noexcept {
        --i;
        return *this;
    }

    /* post-decrement */
    inline constexpr Short operator--(int) noexcept {
        Short ret = *this;
        --i;
        return ret;
    }

    /* add */
    inline constexpr Short & operator+=(Short other) noexcept {
        i += other.i;
        return *this;
    }

    inline constexpr Short & operator+=(int32_t other) noexcept {
        i += other;
        return *this;
    }

    /* subtract */
    inline constexpr Short & operator-=(Short other) noexcept {
        i -= other.i;
        return *this;
    }

    inline constexpr Short & operator-=(int32_t other) noexcept {
        i -= other;
        return *this;
    }

    /* multiply */
    inline constexpr Short & operator*=(Short other) noexcept {
        i *= other.i;
        return *this;
    }

    inline constexpr Short & operator*=(int32_t other) noexcept {
        i *= other;
        return *this;
    }

    /* divide */
    inline constexpr Short & operator/=(Short other) noexcept {
        i /= other.i;
        return *this;
    }

    inline constexpr Short & operator/=(int32_t other) noexcept {
        i /= other;
        return *this;
    }

    /* modulus */
    inline constexpr Short & operator%=(Short other) noexcept {
        i %= other.i;
        return *this;
    }

    inline constexpr Short & operator%=(int32_t other) noexcept {
        i %= other;
        return *this;
    }

    /* bitwise and */
    inline constexpr Short & operator&=(Short other) noexcept {
        i &= other.i;
        return *this;
    }

    inline constexpr Short & operator&=(int32_t other) noexcept {
        i &= other;
        return *this;
    }

    /* bitwise or */
    inline constexpr Short & operator|=(Short other) noexcept {
        i |= other.i;
        return *this;
    }

    inline constexpr Short & operator|=(int32_t other) noexcept {
        i |= other;
        return *this;
    }

    /* bitwise xor */
    inline constexpr Short & operator^=(Short other) noexcept {
        i ^= other.i;
        return *this;
    }

    inline constexpr Short & operator^=(int32_t other) noexcept {
        i ^= other;
        return *this;
    }

    /* bitwise lshift */
    inline constexpr Short & operator<<=(uint8_t count) noexcept {
        i <<= count;
        return *this;
    }

    /* bitwise rshift */
    inline constexpr Short & operator>>=(uint8_t count) noexcept {
        i >>= count;
        return *this;
    }
#else // !CRYSP_SHORT_REF_INPLACE
    /* assign */
    inline constexpr Short & operator=(int32_t i) noexcept {
        return (*this) = Short{i};
    }

    /* pre-increment */
    inline constexpr Short & operator++() noexcept {
        return *this = Short{i + 1};
    }

    /* post-increment */
    inline constexpr Short operator++(int) noexcept {
        Short ret = *this;
        *this = Short{i + 1};
        return ret;
    }

    /* pre-decrement */
    inline constexpr Short & operator--() noexcept {
        return *this = Short{i - 1};
    }

    /* post-decrement */
    inline constexpr Short operator--(int) noexcept {
        Short ret = *this;
        *this = Short{i - 1};
        return ret;
    }

    /* add */
    inline constexpr Short & operator+=(Short other) noexcept {
        return *this = Short{i + other.i};
    }

    inline constexpr Short & operator+=(int32_t other) noexcept {
        return *this = Short{i + other};
    }

    /* subtract */
    inline constexpr Short & operator-=(Short other) noexcept {
        return *this = Short{i - other.i};
    }

    inline constexpr Short & operator-=(int32_t other) noexcept {
        return *this = Short{i - other};
    }

    /* multiply */
    inline constexpr Short & operator*=(Short other) noexcept {
        return *this = Short{i * other.i};
    }

    inline constexpr Short & operator*=(int32_t other) noexcept {
        return *this = Short{i * other};
    }

    /* divide */
    inline constexpr Short & operator/=(Short other) noexcept {
        return *this = Short{i / other.i};
    }

    inline constexpr Short & operator/=(int32_t other) noexcept {
        return *this = Short{i / other};
    }

    /* modulus */
    inline constexpr Short & operator%=(Short other) noexcept {
        return *this = Short{i % other.i};
    }

    inline constexpr Short & operator%=(int32_t other) noexcept {
        return *this = Short{i % other};
    }

    /* bitwise and */
    inline constexpr Short & operator&=(Short other) noexcept {
        // preserves tag
        return *this = Short{bits & other.bits, bits_constructor{}};
    }

    inline constexpr Short & operator&=(int32_t other) noexcept {
        return *this = Short{i & other};
    }

    /* bitwise or */
    inline constexpr Short & operator|=(Short other) noexcept {
        // preserves tag
        return *this = Short{bits | other.bits, bits_constructor{}};
    }

    inline constexpr Short & operator|=(int32_t other) noexcept {
        // preserves tag
        return *this = Short{bits | uint32_t(other)};
    }

    /* bitwise xor */
    inline constexpr Short & operator^=(Short other) noexcept {
        return *this = Short{i ^ other.i};
    }

    inline constexpr Short & operator^=(int32_t other) noexcept {
        return *this = Short{i ^ other};
    }

    /* bitwise lshift */
    inline constexpr Short & operator<<=(uint8_t count) noexcept {
        return *this = Short{i << count};
    }

    /* bitwise rshift */
    inline constexpr Short & operator>>=(uint8_t count) noexcept {
        return *this = Short{i >> count};
    }
#endif // CRYSP_SHORT_REF_INPLACE
};

constexpr Short short_max{int32_t(0x7fffffffl)}, short_min{int32_t(-0x80000000l)};

/* relational operators */
inline constexpr bool operator==(Short a, int32_t b) noexcept {
    return a.val() == b;
}

inline constexpr bool operator==(int32_t a, Short b) noexcept {
    return a == b.val();
}

inline constexpr bool operator!=(Short a, int32_t b) noexcept {
    return a.val() != b;
}

inline constexpr bool operator!=(int32_t a, Short b) noexcept {
    return a != b.val();
}

inline constexpr bool operator<(Short a, Short b) noexcept {
    return a.val() < b.val();
}

inline constexpr bool operator<(Short a, int32_t b) noexcept {
    return a.val() < b;
}

inline constexpr bool operator<(int32_t a, Short b) noexcept {
    return a < b.val();
}

inline constexpr bool operator>(Short a, Short b) noexcept {
    return a.val() > b.val();
}

inline constexpr bool operator>(Short a, int32_t b) noexcept {
    return a.val() > b;
}

inline constexpr bool operator>(int32_t a, Short b) noexcept {
    return a > b.val();
}

inline constexpr bool operator<=(Short a, Short b) noexcept {
    return a.val() <= b.val();
}

inline constexpr bool operator<=(Short a, int32_t b) noexcept {
    return a.val() <= b;
}

inline constexpr bool operator<=(int32_t a, Short b) noexcept {
    return a <= b.val();
}

inline constexpr bool operator>=(Short a, Short b) noexcept {
    return a.val() >= b.val();
}

inline constexpr bool operator>=(Short a, int32_t b) noexcept {
    return a.val() >= b;
}

inline constexpr bool operator>=(int32_t a, Short b) noexcept {
    return a >= b.val();
}

/* arithmetic operators */
#ifdef CRYSP_SHORT_OBJ_INPLACE
inline constexpr Short operator+(Short a, Short b) noexcept {
    return a += b;
}

inline constexpr Short operator+(Short a, int32_t b) noexcept {
    return a += b;
}

inline constexpr Short operator+(int32_t a, Short b) noexcept {
    return b += a;
}

inline constexpr Short operator-(Short a, Short b) noexcept {
    return a -= b;
}

inline constexpr Short operator-(Short a, int32_t b) noexcept {
    return a -= b;
}

inline constexpr Short operator-(int32_t a, Short b) noexcept {
    return b = a - b.val();
}

inline constexpr Short operator*(Short a, Short b) noexcept {
    return a *= b;
}

inline constexpr Short operator*(Short a, int32_t b) noexcept {
    return a *= b;
}

inline constexpr Short operator*(int32_t a, Short b) noexcept {
    return b *= a;
}

inline constexpr Short operator/(Short a, Short b) noexcept {
    return a /= b;
}

inline constexpr Short operator/(Short a, int32_t b) noexcept {
    return a /= b;
}

inline constexpr Short operator/(int32_t a, Short b) noexcept {
    return b = a / b.val();
}

inline constexpr Short operator%(Short a, Short b) noexcept {
    return a %= b;
}

inline constexpr Short operator%(Short a, int32_t b) noexcept {
    return a %= b;
}

inline constexpr Short operator%(int32_t a, Short b) noexcept {
    return b = a % b.val();
}

inline constexpr Short operator&(Short a, Short b) noexcept {
    return a &= b;
}

inline constexpr Short operator&(Short a, int32_t b) noexcept {
    return a &= b;
}

inline constexpr Short operator&(int32_t a, Short b) noexcept {
    return b &= a;
}

inline constexpr Short operator|(Short a, Short b) noexcept {
    return a |= b;
}

inline constexpr Short operator|(Short a, int32_t b) noexcept {
    return a |= b;
}

inline constexpr Short operator|(int32_t a, Short b) noexcept {
    return b |= a;
}

inline constexpr Short operator^(Short a, Short b) noexcept {
    return a ^= b;
}

inline constexpr Short operator^(Short a, int32_t b) noexcept {
    return a ^= b;
}

inline constexpr Short operator^(int32_t a, Short b) noexcept {
    return b ^= a;
}

inline constexpr Short operator<<(Short a, uint8_t b) noexcept {
    return a <<= b;
}

inline constexpr Short operator>>(Short a, uint8_t b) noexcept {
    return a >>= b;
}

#else // !CRYSP_SHORT_OBJ_INPLACE
inline constexpr Short operator+(Short a, Short b) noexcept {
    return Short{a.val() + b.val()};
}

inline constexpr Short operator+(Short a, int32_t b) noexcept {
    return Short{a.val() + b};
}

inline constexpr Short operator+(int32_t a, Short b) noexcept {
    return Short{a + b.val()};
}

inline constexpr Short operator-(Short a, Short b) noexcept {
    return Short{a.val() - b.val()};
}

inline constexpr Short operator-(Short a, int32_t b) noexcept {
    return Short{a.val() - b};
}

inline constexpr Short operator-(int32_t a, Short b) noexcept {
    return Short{a - b.val()};
}

inline constexpr Short operator*(Short a, Short b) noexcept {
    return Short{a.val() * b.val()};
}

inline constexpr Short operator*(Short a, int32_t b) noexcept {
    return Short{a.val() * b};
}

inline constexpr Short operator*(int32_t a, Short b) noexcept {
    return Short{a * b.val()};
}

inline constexpr Short operator/(Short a, Short b) noexcept {
    return Short{a.val() / b.val()};
}

inline constexpr Short operator/(Short a, int32_t b) noexcept {
    return Short{a.val() / b};
}

inline constexpr Short operator/(int32_t a, Short b) noexcept {
    return Short{a / b.val()};
}

inline constexpr Short operator%(Short a, Short b) noexcept {
    return Short{a.val() % b.val()};
}

inline constexpr Short operator%(Short a, int32_t b) noexcept {
    return Short{a.val() % b};
}

inline constexpr Short operator%(int32_t a, Short b) noexcept {
    return Short{a % b.val()};
}

inline constexpr Short operator&(Short a, Short b) noexcept {
    return Short{a.debug_bits() & b.debug_bits(), Short::bits_constructor{}};
}

inline constexpr Short operator&(Short a, int32_t b) noexcept {
    return Short{a.val() & b};
}

inline constexpr Short operator&(int32_t a, Short b) noexcept {
    return Short{a & b.val()};
}

inline constexpr Short operator|(Short a, Short b) noexcept {
    return Short{a.debug_bits() | b.debug_bits(), Short::bits_constructor{}};
}

inline constexpr Short operator|(Short a, int32_t b) noexcept {
    return Short{a.debug_bits() | uint32_t(b), Short::bits_constructor{}};
}

inline constexpr Short operator|(int32_t a, Short b) noexcept {
    return Short{uint32_t(a) | b.debug_bits(), Short::bits_constructor{}};
}

inline constexpr Short operator^(Short a, Short b) noexcept {
    return Short{a.val() ^ b.val()};
}

inline constexpr Short operator^(Short a, int32_t b) noexcept {
    return Short{a.val() ^ b};
}

inline constexpr Short operator^(int32_t a, Short b) noexcept {
    return Short{a ^ b.val()};
}

inline constexpr Short operator<<(Short a, uint8_t b) noexcept {
    return Short{a.val() << b};
}

inline constexpr Short operator>>(Short a, uint8_t b) noexcept {
    return Short{a.val() >> b};
}
#endif // CRYSP_SHORT_OBJ_INPLACE

CRYSP_NS_END

#endif // CRYSP_SHORT_HPP
