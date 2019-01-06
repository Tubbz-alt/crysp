#ifndef CRYSP_DOUBLE_HPP
#define CRYSP_DOUBLE_HPP

#include "t.hpp"

class Double : public T {
public:
    inline constexpr Double() noexcept : T(0.0) {
    }

    explicit inline constexpr Double(double real) noexcept
    /**/ : T(real) {
    }

    /*
    inline constexpr Double(const Double & other) = default;
    inline constexpr Double & operator=(const Double & other) = default;
    inline ~Double() = default;
    */
    
    inline constexpr double val() const noexcept {
        return real;
    }
  
    inline constexpr Double & operator=(double real) noexcept {
        return (*this) = Double{real};
    }

    inline constexpr bool operator<(Double other) noexcept {
        return real < other.real;
    }
    
    /* pre-increment */
    inline constexpr Double & operator++() noexcept {
        ++real;
        return *this;
    }

    /* post-increment */
    inline constexpr Double operator++(int) noexcept {
        Double ret = *this;
        ++real;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Double & operator--() noexcept {
        --real;
        return *this;
    }

    /* post-decrement */
    inline constexpr Double operator--(int) noexcept {
        Double ret = *this;
        --real;
        return ret;
    }

    /* identity */
    inline constexpr Double & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Double & operator-() noexcept {
        real = -real;
        return *this;
    }

    /* boolean negate */
    inline constexpr Double & operator!() noexcept {
        real = !real;
        return *this;
    }

    /* add */
    inline constexpr Double & operator+=(Double other) noexcept {
        real += other.real;
        return *this;
    }

    /* subtract */
    inline constexpr Double & operator-=(Double other) noexcept {
        real -= other.real;
        return *this;
    }

    /* multiply */
    inline constexpr Double & operator*=(Double other) noexcept {
        real *= other.real;
        return *this;
    }

    /* divide */
    inline constexpr Double & operator/=(Double other) noexcept {
        real /= other.real;
        return *this;
    }
};


inline constexpr bool operator>(Double a, Double b) noexcept {
    return b < a;
}

inline constexpr bool operator<=(Double a, Double b) noexcept {
    return !(b < a);
}

inline constexpr bool operator>=(Double a, Double b) noexcept {
    return !(a < b);
}



inline constexpr Double operator+(Double a, Double b) noexcept {
    return a += b;
}

inline constexpr Double operator-(Double a, Double b) noexcept {
    return a -= b;
}

inline constexpr Double operator*(Double a, Double b) noexcept {
    return a *= b;
}

inline constexpr Double operator/(Double a, Double b) noexcept {
    return a /= b;
}


#endif // CRYSP_DOUBLE_HPP
