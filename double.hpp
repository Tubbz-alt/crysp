#ifndef CRYSP_DOUBLE_HPP
#define CRYSP_DOUBLE_HPP

#include "t.hpp"
#include "float.hpp"

class Double : public T {
private:
    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        switch (bits >> 51) {
        case 0x7FF0 >> 3: // +inf or signaling +NaN
        case 0x7FF8 >> 3: // quiet +NaN
        case 0xFFF0 >> 3: // -inf or signaling -NaN
        case 0xFFF8 >> 3: // quiet -NaN
            return (bits << 13) == 0;
        default:
            return true;
        }
    }

public:
    inline constexpr Double() noexcept : T(0.0) {
    }

    /*implicit*/ inline constexpr Double(double dbl) noexcept
    /**/ : T(dbl) {
    }

    /*
     * convert single-precision Float to double-precision Double
     */
    explicit inline constexpr Double(Float fl) noexcept
        : T(double(fl.val())) {
    }

    /*
    inline constexpr Double(const Double & other) = default;
    inline constexpr Double & operator=(const Double & other) = default;
    inline ~Double() = default;
    */
    
    inline constexpr double val() const noexcept {
        return dbl;
    }

    inline constexpr type_id type() const noexcept {
        return double_id;
    }

    enum {
        static_type = double_id,
    };

    /* not strictly needed, constructor Double(double) is implicit */
    inline constexpr Double & operator=(double other) noexcept {
        return (*this) = Double{other};
    }

    /* pre-increment */
    inline constexpr Double & operator++() noexcept {
        ++dbl;
        return *this;
    }

    /* post-increment */
    inline constexpr Double operator++(int) noexcept {
        Double ret = *this;
        ++dbl;
        return ret;
    }

    /* pre-decrement */
    inline constexpr Double & operator--() noexcept {
        --dbl;
        return *this;
    }

    /* post-decrement */
    inline constexpr Double operator--(int) noexcept {
        Double ret = *this;
        --dbl;
        return ret;
    }

    /* identity */
    inline constexpr Double & operator+() noexcept {
        return *this;
    }

    /* flip sign */
    inline constexpr Double operator-() noexcept {
        return Double{-dbl};
    }

    /* boolean negate */
    inline constexpr Double operator!() noexcept {
        return Double{double(!dbl)};
    }

    /* add */
    inline constexpr Double & operator+=(Double other) noexcept {
        dbl += other.dbl;
        return *this;
    }

    /* subtract */
    inline constexpr Double & operator-=(Double other) noexcept {
        dbl -= other.dbl;
        return *this;
    }

    /* multiply */
    inline constexpr Double & operator*=(Double other) noexcept {
        dbl *= other.dbl;
        return *this;
    }

    /* divide */
    inline constexpr Double & operator/=(Double other) noexcept {
        dbl /= other.dbl;
        return *this;
    }
};


/* op(Double, Double) */
inline constexpr bool operator<(Double a, Double b) noexcept {
    return a.val() < b.val();
}

inline constexpr bool operator>(Double a, Double b) noexcept {
    return a.val() > b.val();
}

inline constexpr bool operator<=(Double a, Double b) noexcept {
    return a.val() <= b.val();
}

inline constexpr bool operator>=(Double a, Double b) noexcept {
    return a.val() >= b.val();
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



/* op(Double, double) */
inline constexpr bool operator<(Double a, double b) noexcept {
    return a.val() < b;
}

inline constexpr bool operator>(Double a, double b) noexcept {
    return a.val() > b;
}

inline constexpr bool operator<=(Double a, double b) noexcept {
    return a.val() <= b;
}

inline constexpr bool operator>=(Double a, double b) noexcept {
    return a.val() >= b;
}




/* op(double, Double) */
inline constexpr bool operator<(double a, Double b) noexcept {
    return a < b.val();
}

inline constexpr bool operator>(double a, Double b) noexcept {
    return a > b.val();
}

inline constexpr bool operator<=(double a, Double b) noexcept {
    return a <= b.val();
}

inline constexpr bool operator>=(double a, Double b) noexcept {
    return a >= b.val();
}



#endif // CRYSP_DOUBLE_HPP
