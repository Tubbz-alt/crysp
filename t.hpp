#ifndef CRYSP_T_HPP
#define CRYSP_T_HPP

#include <cstdint>
#include <endian.h>
#include "impl.hpp"

class T {
private:
    friend class Fixnum;
    friend class Float;
    friend class Double;
    friend class Int;
    friend class Null;
    template<class E> friend class Obj;
    friend class Rune;
    friend class Symbol;
    
    union {
        uint64_t  bits;
        double    real; // NaN if not a double
        uint8_t * addr;
#ifdef __LITTLE_ENDIAN__
        struct {
            int32_t i;
            uint32_t i_tag;
        };
        struct {
            float    f;
            uint32_t f_tag;
        };
#else
        struct {
            uint32_t i_tag;
            int32_t  i;
        };
        struct {
            uint32_t f_tag;
            float    f;
        };
#endif // __LITTLE_ENDIAN__
    };

    explicit inline constexpr T(uint64_t bits) noexcept : bits(bits) {
    }
    explicit inline constexpr T(uint8_t *addr) noexcept : addr(addr) {
    }
    explicit inline constexpr T(double real) noexcept : real(real) {
    }
    
#ifdef __LITTLE_ENDIAN__
    explicit inline constexpr T(float f) noexcept
    : f(f), f_tag(impl::float_tag >> 32) {
    }
    explicit inline constexpr T(int32_t i, uint32_t i_tag) noexcept
    : i(i), i_tag(i_tag) {
    }
#else
    explicit inline constexpr T(float f) noexcept
    : f_tag(impl::float_tag >> 32), f(f) {
    }
    explicit inline constexpr T(int32_t i, uint32_t i_tag) noexcept
    : i_tag(i_tag), i(i) {
    }
#endif
    
public:
    inline constexpr T() noexcept
    : bits(impl::t_bits) {
    }

    /*
    inline constexpr T(const T & other) = default;
    inline constexpr T & operator=(const T & other) = default;
    inline ~T() = default;
    */
    
    inline uint64_t debug_bits() const noexcept {
	return bits;
    }

    inline operator bool() const noexcept {
	return bits != impl::nil_bits;
    }
};

#endif // CRYSP_T_HPP
