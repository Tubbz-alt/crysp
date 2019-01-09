#ifndef CRYSP_FLOAT_HPP
#define CRYSP_FLOAT_HPP

#include "t.hpp"

class Float : public T {
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

    /* not strictly needed, constructor Float(float) is implicit */
    inline Float & operator=(float other) noexcept {
        return (*this) = Float{other};
    }

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
};

/* op(Float, Float) */
inline constexpr bool operator<(Float a, Float b) noexcept {
    return a.val() < b.val();
}

inline constexpr bool operator>(Float a, Float b) noexcept {
    return a.val() > b.val();
}

inline constexpr bool operator<=(Float a, Float b) noexcept {
    return a.val() <= b.val();
}

inline constexpr bool operator>=(Float a, Float b) noexcept {
    return a.val() >= b.val();
}



inline constexpr Float operator+(Float a, Float b) noexcept {
    return Float{a.val() + b.val()};
}

inline constexpr Float operator-(Float a, Float b) noexcept {
    return Float{a.val() - b.val()};
}

inline constexpr Float operator*(Float a, Float b) noexcept {
    return Float{a.val() * b.val()};
}

inline constexpr Float operator/(Float a, Float b) noexcept {
    return Float{a.val() / b.val()};
}



/* op(Float, float) */
inline constexpr bool operator<(Float a, float b) noexcept {
    return a.val() < b;
}

inline constexpr bool operator>(Float a, float b) noexcept {
    return a.val() > b;
}

inline constexpr bool operator<=(Float a, float b) noexcept {
    return a.val() <= b;
}

inline constexpr bool operator>=(Float a, float b) noexcept {
    return a.val() >= b;
}



inline constexpr Float operator+(Float a, float b) noexcept {
    return Float{a.val() + b};
}

inline constexpr Float operator-(Float a, float b) noexcept {
    return Float{a.val() - b};
}

inline constexpr Float operator*(Float a, float b) noexcept {
    return Float{a.val() * b};
}

inline constexpr Float operator/(Float a, float b) noexcept {
    return Float{a.val() / b};
}


/* op(float, Float) */
inline constexpr bool operator<(float a, Float b) noexcept {
    return a < b.val();
}

inline constexpr bool operator>(float a, Float b) noexcept {
    return a > b.val();
}

inline constexpr bool operator<=(float a, Float b) noexcept {
    return a <= b.val();
}

inline constexpr bool operator>=(float a, Float b) noexcept {
    return a >= b.val();
}


inline constexpr Float operator+(float a, Float b) noexcept {
    return Float{a + b.val()};
}

inline constexpr Float operator-(float a, Float b) noexcept {
    return Float{a - b.val()};
}

inline constexpr Float operator*(float a, Float b) noexcept {
    return Float{a * b.val()};
}

inline constexpr Float operator/(float a, Float b) noexcept {
    return Float{a / b.val()};
}

#endif // CRYSP_FLOAT_HPP
