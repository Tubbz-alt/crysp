#ifndef CRYSP_T_HPP
#define CRYSP_T_HPP

#include <cstdio>
#include <endian.h>
#include "crysp/impl.hpp"

CRYSP_NS_START

class Type;

class T {
private:
    friend class Float;
    friend class Double;
    friend class Int;
    template<class E> friend class Obj;
    friend class Pair;
    friend class Rune;
    friend class Short;
    friend class Symbol;
    friend class Type;
    friend class Utf8;
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
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    };

    inline void * addr() noexcept {
        return (void *)(bits & impl::pointer_unmask);
    }

    inline const void * addr() const noexcept {
        return (const void *)(bits & impl::pointer_unmask);
    }

    explicit inline constexpr T(uint64_t bits) noexcept : bits(bits) {
    }
    explicit inline constexpr T(double dbl) noexcept : dbl(dbl) {
    }
    
#if __BYTE_ORDER == __LITTLE_ENDIAN
    explicit inline constexpr T(float fl) noexcept
    /**/ : fl(fl), fl_tag(impl::float_tag >> 32) {
    }
    explicit inline constexpr T(int32_t i, uint32_t i_tag) noexcept
    /**/ : i(i), i_tag(i_tag) {
    }
#else
    explicit inline constexpr T(float fl) noexcept
    /**/ : fl_tag(impl::float_tag >> 32), fl(fl) {
    }
    explicit inline constexpr T(int32_t i, uint32_t i_tag) noexcept
    /**/ : i_tag(i_tag), i(i) {
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

    // defined in type.hpp
    inline constexpr Type type() const noexcept;

    // constexpr... must be in header file
    CRYSP_NOINLINE constexpr type::id type_id() const noexcept {
        switch (bits >> 48) {
        case impl::float_tag >> 48:
            return type::float_id;
        case impl::short_tag >> 48:
            return type::short_id;
        case impl::type_tag >> 48:
            return type::type_id;
        case impl::rune_tag >> 48:
            return type::rune_id;
        case impl::utf8_tag >> 48:
            return type::utf8_id;
        case (impl::int_tag >> 48) + 0:
        case (impl::int_tag >> 48) + 1:
        case (impl::int_tag >> 48) + 2:
        case (impl::int_tag >> 48) + 3:
            return type::int_id;
        }
        
        uint64_t addr52 = 0;

        if ((bits >> 52) == (impl::pointer_tag >> 52) &&
            (addr52 = (bits & ~impl::pointer_mask)) != 0 && /* skip +inf */
            addr52 != (uint64_t(1) << 51)) /* skip +NaN */ {
            
            switch (bits & 0xF) {
            case impl::struct_tag & 0xF:
                return type::struct_id;
            case impl::pair_tag & 0xF:
                return type::pair_id;
            case impl::symbol_tag & 0xF:
                return type::symbol_id;
            case impl::func_tag & 0xF:
                return type::func_id;
            default:
                return type::unknown_id;
            }
        }
        return type::double_id;
    }

    // return number of written bytes
    int print(FILE *out) const;
};

constexpr const T t;

CRYSP_NS_END

#endif // CRYSP_T_HPP
