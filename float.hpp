#ifndef CRYSP_FLOAT_HPP
#define CRYSP_FLOAT_HPP

#include "t.hpp"

class Float : public T {
public:
    inline constexpr Float() noexcept : T(0.0f) {
    }

    inline constexpr Float(float f) noexcept : T(f) {
    }

    /*
    inline constexpr Float(const Float & other) = default;
    inline constexpr Float & operator=(const Float & other) = default;
    inline ~Float() = default;
    */
    
    inline operator bool() const noexcept {
	return true;
    }

    inline operator float() const noexcept {
	return f;
    }

    inline float value() const noexcept {
        return f;
    }
};

#endif // CRYSP_FLOAT_HPP
