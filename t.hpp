#ifndef CRYSP_T_HPP
#define CRYSP_T_HPP

#include <cstdint>
#include <cstdio>
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
#if __BYTE_ORDER == __LITTLE_ENDIAN
        struct {
	    int32_t  i; // rune or 32-bit integer
            uint32_t i_tag;
        };
        struct {
            float    fl;
            uint32_t fl_tag;
        };
#else
        struct {
            uint32_t i_tag;
            int32_t  i;
        };
        struct {
            uint32_t fl_tag;
            float    fl;
        };
#endif // __LITTLE_ENDIAN__
    };

    explicit inline constexpr T(uint64_t bits) noexcept : bits(bits) {
    }
    explicit inline constexpr T(uint8_t *addr) noexcept : addr(addr) {
    }
    explicit inline constexpr T(double real) noexcept : real(real) {
    }
    
#if __BYTE_ORDER == __LITTLE_ENDIAN
    explicit inline constexpr T(float fl) noexcept
    /**/ : fl(fl), fl_tag(impl::float_tag >> 32) {
    }
    explicit inline constexpr T(int32_t ch) noexcept
    /**/ : i(ch), i_tag(impl::rune_tag >> 32) {
    }
#else
    explicit inline constexpr T(float fl) noexcept
    /**/ : fl_tag(impl::float_tag >> 32), fl(fl) {
    }
    explicit inline constexpr T(int32_t ch) noexcept
    /**/ : i_tag(impl::rune_tag >> 32), i(ch) {
    }
#endif
    
public:
    inline constexpr T() noexcept
    /**/ : bits(impl::t_bits) {
    }

    /*
    inline constexpr T(const T & other) = default;
    inline constexpr T & operator=(const T & other) = default;
    inline ~T() = default;
    */
    
    inline uint64_t debug_bits() const noexcept {
	return bits;
    }

    inline bool operator==(T other) const noexcept {
        return bits == other.bits;
    }

    inline bool operator!=(T other) const noexcept {
        return bits != other.bits;
    }

    void print(FILE *out) const;
};

extern const T t;

#endif // CRYSP_T_HPP
