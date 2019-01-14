#ifndef CRYSP_SHORT_HPP
#define CRYSP_SHORT_HPP

#include "int.hpp"

/**
 * 32-bit signed integer.
 * operations on Short are wrapping, i.e. any overflow is truncated modulo 32 bits,
 * except methods with a check_overflow_t argument, which throw an exception on overflow.
 */
class Short : public Int {
private:

    static inline uint64_t check(uint64_t bits) /* throw(std::bad_cast) */ {
        uint32_t hi = bits >> 32;
        if (hi != (impl::int_tag >> 32) && ~hi != 0) {
            impl::throw_bad_cast();
        }
        return bits;
    }

public:
    inline constexpr Short() noexcept
    /**/ : Int{} {
    }

    explicit inline constexpr Short(int32_t i) noexcept
        // sign-extend to 64 bits
        : Int{int64_t(i)} {
    }

    /*
    inline constexpr Short(const Short & other) = default;
    inline constexpr Short & operator=(const Short & other) = default;
    inline ~Short() = default;
    */
    
    inline constexpr int32_t val() const noexcept {
        return i;
    }

#ifdef CRYSP_32BIT_THIS_INPLACE
    inline constexpr Short & operator=(int32_t other) noexcept {
        i = other;
        return *this;
    }
#else
    inline constexpr Short & operator=(int32_t i) noexcept {
        return (*this) = Short{i};
    }
#endif

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
    
#ifdef CRYSP_32BIT_THIS_INPLACE
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
#else // !CRYSP_32BIT_THIS_INPLACE
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
#endif // CRYSP_32BIT_THIS_INPLACE
};

constexpr Short short_max{int32_t(0x7fffffffl)}, short_min{int32_t(-0x80000000l)};

/* relational operators */
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
#ifdef CRYSP_32BIT_OP_INPLACE
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
#else // !CRYSP_32BIT_OP_INPLACE
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
#endif // CRYSP_32BIT_OP_INPLACE

#endif // CRYSP_SHORT_HPP
