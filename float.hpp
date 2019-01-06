#ifndef CRYSP_FLOAT_HPP
#define CRYSP_FLOAT_HPP

#include "t.hpp"

class Float : public T {
public:
    inline constexpr Float() noexcept : T(0.0f) {
    }

    inline constexpr Float(float fl) noexcept : T(fl) {
    }

    /*
    inline constexpr Float(const Float & other) = default;
    inline constexpr Float & operator=(const Float & other) = default;
    inline ~Float() = default;
    */
    
    inline float val() const noexcept {
        return fl;
    }

    inline Float & operator=(float fl) noexcept {
        return (*this) = Float{fl};
    }
};

#endif // CRYSP_FLOAT_HPP
