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
    
    inline double val() const noexcept {
        return real;
    }
  
    inline Double & operator=(double real) noexcept {
        return (*this) = Double{real};
    }
};

#endif // CRYSP_DOUBLE_HPP
