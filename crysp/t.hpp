#ifndef CRYSP_T_HPP
#define CRYSP_T_HPP

#include <cstdio>
#include <endian.h>
#include "impl.hpp"

CRYSP_NS_START

class Type;

class T {
private:
    friend class Float;
    friend class Func;
    friend class Double;
    friend class Long;
    template<class E> friend class Obj;
    friend class Pair;
    friend class Rune;
    friend class Int;
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
    /*
     * default constructor: create a T containing nil.
     * It was found more useful in practice than
     * the alternative to create a T containing t.
     *
     * To create a T containing t, call T::t()
     * or just use the global variable t
     */
    inline constexpr T() noexcept
    /**/ : bits(impl::nil_bits) {
    }

    // return a T containing t
    static inline constexpr T t() noexcept {
        return T{impl::t_bits};
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
        static_assert(((impl::type_tag  >> 48) & 0xF) == impl::tag(type::type_id),  "mismatch between impl::type_tag  and type::type_id");
        static_assert(((impl::float_tag >> 48) & 0xF) == impl::tag(type::float_id), "mismatch between impl::float_tag and type::float_id");
        static_assert(((impl::int_tag   >> 48) & 0xF) == impl::tag(type::int_id),   "mismatch between impl::int_tag   and type::int_id");
        static_assert(((impl::rune_tag  >> 48) & 0xF) == impl::tag(type::rune_id),  "mismatch between impl::rune_tag  and type::rune_id");
        static_assert(((impl::utf8_tag  >> 48) & 0xF) == impl::tag(type::utf8_id),  "mismatch between impl::utf8_tag  and type::utf8_id");
       
        switch (bits >> 48) {
        case impl::type_tag  >> 48: // return type::type_id;
        case impl::float_tag >> 48: // return type::float_id;
        case impl::int_tag   >> 48: // return type::int_id;
        case impl::rune_tag  >> 48: // return type::rune_id;
        case impl::utf8_tag  >> 48: // return type::utf8_id;
	   return type::id((bits >> 48) & 0xF);
           
           static_assert(((impl::type_tag  >> 48) & 0xF) == type::type_id  &&
                         ((impl::float_tag >> 48) & 0xF) == type::float_id &&
                         ((impl::int_tag   >> 48) & 0xF) == type::int_id   &&
                         ((impl::rune_tag  >> 48) & 0xF) == type::rune_id  &&
                         ((impl::utf8_tag  >> 48) & 0xF) == type::utf8_id,
                         "mismatch between impl::*_tag and type::*_id. "
                         "please fix crysp/impl.hpp");

        case (impl::long_tag >> 48) + 0:
        case (impl::long_tag >> 48) + 1:
        case (impl::long_tag >> 48) + 2:
        case (impl::long_tag >> 48) + 3:
            return type::long_id;
        }
        
        uint64_t addr52 = 0;

        if ((bits >> 52) == (impl::pointer_tag >> 52) &&
            (addr52 = (bits & ~impl::pointer_mask)) != 0 && /* skip +inf */
            addr52 != (uint64_t(1) << 51)) /* skip +NaN */ {
            
            switch (bits & 0xF) {
            case impl::obj_tag & 0xF:    // return type::obj_id;
            case impl::pair_tag & 0xF:   // return type::pair_id;
            case impl::symbol_tag & 0xF: // return type::symbol_id;
            case impl::func_tag & 0xF:   // return type::func_id;
                return type::id((bits & 0xF) | 0x10);

                static_assert((impl::obj_tag    & 0xF) == (type::obj_id    & 0xF) &&
                              (impl::pair_tag   & 0xF) == (type::pair_id   & 0xF) &&
                              (impl::symbol_tag & 0xF) == (type::symbol_id & 0xF) &&
                              (impl::func_tag   & 0xF) == (type::func_id   & 0xF),
                              "mismatch between impl::*_tag and type::*_id. "
                              "please fix crysp/impl.hpp");
            default:
                return type::t_id;
            }
        }
        return type::double_id;
    }

    enum {
        static_type_id = type::t_id,
    };

    // return number of written bytes
    int print(FILE *out) const;
};

constexpr const T t = T::t();

CRYSP_NS_END

#endif // CRYSP_T_HPP
