#ifndef CRYSP_UTF8_HPP
#define CRYSP_UTF8_HPP

#include "rune.hpp"

union utf8 {
    uint32_t val;
    char byte[4];

    explicit inline constexpr utf8(uint32_t val) noexcept
        : val(val) {
    }

    inline constexpr utf8(char a, char b, char c = 0, char d = 0) noexcept
        : byte{a, b, c, d} {
    }

    inline constexpr int size() const noexcept {
        if (byte[1] == 0)
            return 1;
        if (byte[2] == 0)
            return 2;
        if (byte[3] == 0)
            return 3;
        return 4;
    }

#if __BYTE_ORDER == __LITTLE_ENDIAN
    /* encode Unicode codepoint to 4-byte utf-8 */
    static noinline constexpr uint32_t make(rune r) noexcept {
        uint32_t u = 0;
        if (CRYSP_LIKELY(r <= 0x7F)) {
            u = r;
        } else if (CRYSP_LIKELY(r <= 0x07FF)) {
            u = 0x80C0 | (r >> 6) | ((r & 0x3F) << 8);
        } else if (CRYSP_LIKELY(r <= 0xFFFF)) {
            u = 0x8080E0 |
                (r >> 12) |
                ((r << 2) & 0x3F00) |
                ((r & 0x3F) << 16);
        } else if (CRYSP_LIKELY(r <= 0x10FFFF)) {
            u = 0x808080F0 |
                (r >> 18) |
                ((r >> 4) & 0x3F00) |
                ((r & 0xFC0) << 10) |
                ((r & 0x3F) << 24);
        }
        return u;
    }

    /* decode 4-byte utf-8 to Unicode codepoint */
    static noinline constexpr rune unmake(uint32_t u) noexcept {
        rune r = 0;
        if (CRYSP_LIKELY(u <= 0xFF)) {
            r = u & 0x7F;
        } else if (CRYSP_LIKELY(u <= 0xFFFF)) {
            r = ((u & 0x1F) << 6) | ((u >> 8) & 0x3F);
            if (r <= 0x7F)
                r = 0; // overlong encoding
        } else if (CRYSP_LIKELY(u <= 0xFFFFFF)) {
            r = ((u & 0x0F) << 12) |
                ((u & 0x3F00) >> 2) |
                ((u >> 16) & 0x3F);
            if (r <= 0x07FF)
                r = 0; // overlong encoding
        } else {
            r = ((u & 0x07) << 18) |
                ((u & 0x3F00) << 4) |
                ((u >> 10) & 0xFC0) |
                ((u >> 24) & 0x3F);
            if (r <= 0xFFFF || r > 0x10FFFF)
                r = 0; // overlong encoding or overflow
        }
        return r;
    }
#else
    /* encode Unicode codepoint to 4-byte utf-8 */
    static noinline constexpr uint32_t make(rune r) noexcept {
        uint32_t u = 0;
        if (CRYSP_LIKELY(r <= 0x7F)) {
            u = r << 24;
        } else if (CRYSP_LIKELY(r <= 0x07FF)) {
            u = 0xC0800000 |
                ((r & 0x07C0) << 18) |
                ((r & 0x003F) << 16);
        } else if (CRYSP_LIKELY(r <= 0xFFFF)) {
            u = 0xE0808000u |
                ((r & 0xF000) << 12) |
                ((r & 0x0FC0) << 10) |
                ((r & 0x003F) << 8);
        } else if (CRYSP_LIKELY(r <= 0x10FFFF)) {
            u = 0xF0808080 |
                ((r & 0x1C0000) << 6) |
                ((r & 0x03F000) << 4) |
                ((r & 0x000FC0) << 2) |
                ((r & 0x00003F) << 0);
        }
        return u;
    }

    /* decode 4-byte utf-8 to Unicode codepoint */
    static noinline constexpr rune unmake(uint32_t u) noexcept {
        rune r = 0;
        if (CRYSP_LIKELY((u & 0x00FFFFFF) == 0)) {
            r = u >> 24;
        } else if (CRYSP_LIKELY((u & 0xFFFF) == 0)) {
            r = ((u >> 18) & 0x07C0) |
                ((u >> 16) & 0x003F);
            if (r <= 0x7F)
                r = 0; // overlong encoding
        } else if (CRYSP_LIKELY(u <= 0xFFFFFF)) {
            r = ((u >> 12) & 0xF000) |
                ((u >> 10) & 0x0FC0) |
                ((u >>  8) & 0x003F);
            if (r <= 0x07FF)
                r = 0; // overlong encoding
        } else {
            r = ((r >> 6) & 0x1C0000) |
                ((r >> 4) & 0x03F000) |
                ((r << 2) & 0x000FC0) |
                ((r << 0) & 0x00003F);
            if (r <= 0xFFFF || r > 0x10FFFF)
                r = 0; // overlong encoding or overflow
        }
        return r;
    }
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    
    int print(FILE *out) const;
};


class Utf8 : public T {
private:
    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits >> 48) == (impl::utf8_tag >> 48);
    }

public:
    inline constexpr Utf8() noexcept
    /**/: T{int32_t(0), uint32_t(impl::utf8_tag >> 32)} {
    }

    explicit inline constexpr Utf8(rune r) noexcept
        : T{int32_t(utf8::make(r)), uint32_t(impl::utf8_tag >> 32)} {
    }

    explicit inline constexpr Utf8(Rune r) noexcept
        : T{int32_t(utf8::make(r.val())), uint32_t(impl::utf8_tag >> 32)} {
    }

    explicit inline constexpr Utf8(utf8 u) noexcept
        : T{int32_t(u.val), uint32_t(impl::utf8_tag >> 32)} {
    }

    inline constexpr Utf8(char a, char b, char c = 0, char d = 0) noexcept
        : T{int32_t(utf8(a, b, c, d).val), uint32_t(impl::utf8_tag >> 32)} {
    }

    inline constexpr utf8 val() const noexcept {
        return utf8(uint32_t(i));
    }

    inline constexpr rune val_rune() const noexcept {
        return utf8::unmake(uint32_t(i));
    }

    static inline constexpr Type type() noexcept {
        return Type{type::utf8_id};
    }

    static inline constexpr type::id type_id() noexcept {
        return type::utf8_id;
    }

    enum {
        static_type_id = type::utf8_id,
    };

    inline int print(FILE *out) const {
        return val().print(out);
    }

    inline constexpr int size() const noexcept {
        return val().size();
    }
    
    // return '\0'-terminated sequence of bytes
    inline const char * data() noexcept {
        return reinterpret_cast<const char *>(&i);
    }
};

// declared in rune.hpp
inline constexpr Rune::Rune(Utf8 utf8) noexcept
    : T{int32_t(utf8.val_rune()),
        uint32_t(impl::rune_tag >> 32)} {
}

#endif // CRYSP_UTF8_HPP
