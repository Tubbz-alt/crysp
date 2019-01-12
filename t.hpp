#ifndef CRYSP_T_HPP
#define CRYSP_T_HPP

#include <cstdint> // int32_t, uint64_t
#include <cstdio>
#include <endian.h>
#include "impl.hpp"

class T {
private:
    friend class Fixint;
    friend class Float;
    friend class Double;
    friend class Cons;
    template<class E> friend class Obj;
    friend class Rune;
    friend class Smallint;
    friend class Symbol;
    template<class To> friend bool is(T arg);
    template<class To, class From> friend To cast(From arg);
    
    static inline constexpr bool typecheck(uint64_t) noexcept {
        return true;
    }

    union {
        uint64_t  bits;
        double    dbl; // NaN if not a double
        // uint8_t * addr;
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

    inline constexpr void * addr() noexcept {
        return (void *)(bits & impl::pointer_unmask);
    }
    
    explicit inline constexpr T(uint64_t bits) noexcept : bits(bits) {
    }
    explicit inline constexpr T(double dbl) noexcept : dbl(dbl) {
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
    
    inline constexpr uint64_t debug_bits() const noexcept {
	return bits;
    }

    inline constexpr bool operator==(T other) const noexcept {
        return bits == other.bits;
    }

    inline constexpr bool operator!=(T other) const noexcept {
        return bits != other.bits;
    }

    type_id constexpr type() const noexcept;
    
    void print(FILE *out) const;
};

constexpr T t;


#endif // CRYSP_T_HPP
