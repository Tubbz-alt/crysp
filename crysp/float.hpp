#ifndef CRYSP_FLOAT_HPP
#define CRYSP_FLOAT_HPP

#include "crysp/t.hpp"
#include "crysp/type.hpp"

// optimizations
#define CRYSP_FLOAT_REF_INPLACE

#if defined(__x86_64__) || defined(__x86_64)
# undef CRYSP_FLOAT_OBJ_INPLACE
#else
# define CRYSP_FLOAT_OBJ_INPLACE
#endif

CRYSP_NS_START

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

    inline constexpr Type type() noexcept {
        return Type{type::float_id};
    }

    static inline constexpr type::id type_id() noexcept {
        return type::float_id;
    }

    enum {
          static_type_id = type::float_id,
    };
    
    // return number of written bytes
    int print(FILE *out) const;
    
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

#ifdef CRYSP_FLOAT_REF_INPLACE
    /* not strictly needed, constructor Float(float) is implicit */
    inline constexpr Float & operator=(float other) noexcept {
        fl = other;
        return *this;
    }
    /* pre-increment */
    inline constexpr Float & operator++() noexcept {
        ++fl;
        return *this;
    }

    /* pre-decrement */
    inline constexpr Float & operator--() noexcept {
        --fl;
        return *this;
    }

    /* post-increment */
    inline constexpr Float operator++(int) noexcept {
        Float ret = *this;
        ++fl;
        return ret;
    }

    /* post-decrement */
    inline constexpr Float operator--(int) noexcept {
        Float ret = *this;
        --fl;
        return ret;
    }

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
#else // !CRYSP_FLOAT_REF_INPLACE
    /* not strictly needed, constructor Float(float) is implicit */
    inline constexpr Float & operator=(float other) noexcept {
        return (*this) = Float{other};
    }

    /* pre-increment */
    inline constexpr Float & operator++() noexcept {
        return *this = Float{fl + 1};
    }

    /* pre-decrement */
    inline constexpr Float & operator--() noexcept {
        return *this = Float{fl - 1};
    }

    /* post-increment */
    inline constexpr Float operator++(int) noexcept {
        Float ret = *this;
        *this = Float{fl + 1};
        return ret;
    }

    /* post-decrement */
    inline constexpr Float operator--(int) noexcept {
        Float ret = *this;
        *this = Float{fl - 1};
        return ret;
    }

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
#endif // CRYSP_FLOAT_REF_INPLACE
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
#ifdef CRYSP_FLOAT_OBJ_INPLACE
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
#else // !CRYSP_FLOAT_OBJ_INPLACE
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
#endif // CRYSP_FLOAT_OBJ_INPLACE

CRYSP_NS_END

#endif // CRYSP_FLOAT_HPP
