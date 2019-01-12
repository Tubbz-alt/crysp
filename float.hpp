#ifndef CRYSP_FLOAT_HPP
#define CRYSP_FLOAT_HPP

#include "t.hpp"

class Float : public T {
private:
    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits >> 48) == (impl::float_tag >> 48);
    }

public:
    inline constexpr Float() noexcept : T(0.0f) {
    }

    /*implicit*/ inline constexpr Float(float fl) noexcept : T(fl) {
    }

    /*
    inline constexpr Float(const Float & other) = default;
    inline constexpr Float & operator=(const Float & other) = default;
    inline ~Float() = default;
    */
    
    inline constexpr float val() const noexcept {
        return fl;
    }

    inline constexpr type_id type() const noexcept {
        return float_id;
    }

    enum {
        static_type = float_id,
    };
    
    /* not strictly needed, constructor Float(float) is implicit */
#ifdef CRYSP_64BIT
    inline constexpr Float & operator=(float other) noexcept {
        return (*this) = Float{other};
    }
#else // 32bit or narrower architecture
    inline constexpr Float & operator=(float other) noexcept {
        fl = other;
        return *this;
    }
#endif
    
    /* pre-increment */
    inline constexpr Float & operator++() noexcept {
        ++fl;
        return *this;
    }

    /* post-increment */
    inline constexpr Float operator++(int) noexcept {
        Float ret = *this;
        ++fl;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Float & operator--() noexcept {
        --fl;
        return *this;
    }

    /* post-decrement */
    inline constexpr Float operator--(int) noexcept {
        Float ret = *this;
        --fl;
        return ret;
    }

    /* identity */
    inline constexpr Float & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Float operator-() noexcept {
        return Float{-fl};
    }

    /* boolean negate */
    inline constexpr Float operator!() noexcept {
        return Float{float(!fl)};
    }

#ifdef CRYSP_64BIT
    /* add */
    inline constexpr Float & operator+=(Float other) noexcept {
        return *this = Float{fl + other.fl};
    }

    inline constexpr Float & operator+=(float other) noexcept {
        return *this = Float{fl + other};
    }

    /* subtract */
    inline constexpr Float & operator-=(Float other) noexcept {
        return *this = Float{fl - other.fl};
    }

    inline constexpr Float & operator-=(float other) noexcept {
        return *this = Float{fl - other};
    }

    /* multiply */
    inline constexpr Float & operator*=(Float other) noexcept {
        return *this = Float{fl * other.fl};
    }

    inline constexpr Float & operator*=(float other) noexcept {
        return *this = Float{fl * other};
    }

    /* divide */
    inline constexpr Float & operator/=(Float other) noexcept {
        return *this = Float{fl / other.fl};
    }

    inline constexpr Float & operator/=(float other) noexcept {
        return *this = Float{fl / other};
    }
#else // 32bit or narrower architecture
    /* add */
    inline constexpr Float & operator+=(Float other) noexcept {
        fl += other.fl;
        return *this;
    }

    inline constexpr Float & operator+=(float other) noexcept {
        fl += other;
        return *this;
    }

    /* subtract */
    inline constexpr Float & operator-=(Float other) noexcept {
        fl -= other.fl;
        return *this;
    }

    inline constexpr Float & operator-=(float other) noexcept {
        fl -= other;
        return *this;
    }

    /* multiply */
    inline constexpr Float & operator*=(Float other) noexcept {
        fl *= other.fl;
        return *this;
    }

    inline constexpr Float & operator*=(float other) noexcept {
        fl *= other;
        return *this;
    }

    /* divide */
    inline constexpr Float & operator/=(Float other) noexcept {
        fl /= other.fl;
        return *this;
    }

    inline constexpr Float & operator/=(float other) noexcept {
        fl /= other;
        return *this;
    }
#endif
};

/* relational operators */
inline constexpr bool operator<(Float a, Float b) noexcept {
    return a.val() < b.val();
}

inline constexpr bool operator<(Float a, float b) noexcept {
    return a.val() < b;
}

inline constexpr bool operator<(float a, Float b) noexcept {
    return a < b.val();
}

inline constexpr bool operator>(Float a, Float b) noexcept {
    return a.val() > b.val();
}

inline constexpr bool operator>(Float a, float b) noexcept {
    return a.val() > b;
}

inline constexpr bool operator>(float a, Float b) noexcept {
    return a > b.val();
}

inline constexpr bool operator<=(Float a, Float b) noexcept {
    return a.val() <= b.val();
}

inline constexpr bool operator<=(Float a, float b) noexcept {
    return a.val() <= b;
}

inline constexpr bool operator<=(float a, Float b) noexcept {
    return a <= b.val();
}

inline constexpr bool operator>=(Float a, Float b) noexcept {
    return a.val() >= b.val();
}

inline constexpr bool operator>=(Float a, float b) noexcept {
    return a.val() >= b;
}

inline constexpr bool operator>=(float a, Float b) noexcept {
    return a >= b.val();
}

/* arithmetic operators */
#if defined(CRYSP_64BIT) || defined(__i386__)
inline constexpr Float operator+(Float a, Float b) noexcept {
    return Float{a.val() + b.val()};
}

inline constexpr Float operator+(Float a, float b) noexcept {
    return Float{a.val() + b};
}

inline constexpr Float operator+(float a, Float b) noexcept {
    return Float{a + b.val()};
}

inline constexpr Float operator-(Float a, Float b) noexcept {
    return Float{a.val() - b.val()};
}

inline constexpr Float operator-(Float a, float b) noexcept {
    return Float{a.val() - b};
}

inline constexpr Float operator-(float a, Float b) noexcept {
    return Float{a - b.val()};
}

inline constexpr Float operator*(Float a, Float b) noexcept {
    return Float{a.val() * b.val()};
}

inline constexpr Float operator*(Float a, float b) noexcept {
    return Float{a.val() * b};
}

inline constexpr Float operator*(float a, Float b) noexcept {
    return Float{a * b.val()};
}

inline constexpr Float operator/(Float a, Float b) noexcept {
    return Float{a.val() / b.val()};
}

inline constexpr Float operator/(Float a, float b) noexcept {
    return Float{a.val() / b};
}

inline constexpr Float operator/(float a, Float b) noexcept {
    return Float{a / b.val()};
}
#else // 32bit or narrower architecture
inline constexpr Float operator+(Float a, Float b) noexcept {
    return a += b;
}

inline constexpr Float operator+(Float a, float b) noexcept {
    return a += b;
}

inline constexpr Float operator+(float a, Float b) noexcept {
    return b += a;
}

inline constexpr Float operator-(Float a, Float b) noexcept {
    return a -= b;
}

inline constexpr Float operator-(Float a, float b) noexcept {
    return a -= b;
}

inline constexpr Float operator-(float a, Float b) noexcept {
    return b = a - b.val();
}

inline constexpr Float operator*(Float a, Float b) noexcept {
    return a *= b;
}

inline constexpr Float operator*(Float a, float b) noexcept {
    return a *= b;
}

inline constexpr Float operator*(float a, Float b) noexcept {
    return b *= a;
}

inline constexpr Float operator/(Float a, Float b) noexcept {
    return a /= b;
}

inline constexpr Float operator/(Float a, float b) noexcept {
    return a /= b;
}

inline constexpr Float operator/(float a, Float b) noexcept {
    return b = a / b.val();
}
#endif

#endif // CRYSP_FLOAT_HPP
