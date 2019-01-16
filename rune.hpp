#ifndef CRYSP_RUNE_HPP
#define CRYSP_RUNE_HPP

#include "t.hpp"

typedef int32_t rune; // Unicode is actually a little less than 21 bits

class utf8_t {
public:
    uint8_t byte[4];

    inline constexpr utf8_t() noexcept
    /**/: byte{} {
    }

    explicit inline constexpr utf8_t(const uint8_t bytes[4]) noexcept
        : byte{bytes[0], bytes[1], bytes[2], bytes[3]} {
    }

    inline constexpr utf8_t(uint8_t llo, uint8_t lo,
                            uint8_t hi = 0, uint8_t hhi = 0) noexcept
        : byte{llo, lo, hi, hhi} {
    }

    explicit inline utf8_t(rune ch) noexcept {
        if (ch <= 0x7F) {
            byte[0] = uint8_t(ch);
            byte[1] = byte[2] = byte[3] = 0;
        } else if (ch <= 0x07FF) {
            byte[0] = 0xC0 | (ch >> 6);
            byte[1] = 0x80 | (ch & 0x3F);
            byte[2] = byte[3] = 0;
        } else if (ch <= 0xFFFF) {
            byte[0] = 0xE0 | (ch >> 12);
            byte[1] = 0x80 | ((ch >> 6) & 0x3F);
            byte[2] = 0x80 | (ch & 0x3F);
            byte[3] = 0;
        } else if (ch <= 0x10FFFF) {
            byte[0] = 0xF0 | (ch >> 18);
            byte[1] = 0x80 | ((ch >> 12) & 0x3F);
            byte[2] = 0x80 | ((ch >> 6) & 0x3F);
            byte[3] = 0x80 | (ch & 0x3F);
        } else {
            byte[0] = byte[1] = byte[2] = byte[3] = 0;
        }
    }

    inline constexpr int size() const {
        if (byte[1] == 0)
            return 1;
        if (byte[2] == 0)
            return 2;
        if (byte[3] == 0)
            return 3;
        return 4;
    }

    inline constexpr uint8_t & operator[](uint8_t i) {
        return byte[i];
    }

    inline constexpr const uint8_t & operator[](uint8_t i) const {
        return byte[i];
    }
};

class Rune : public T {
private:
    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits >> 48) == (impl::rune_tag >> 48);
    }

public:
    inline constexpr Rune() noexcept
    /**/: T{int32_t(0), int32_t(impl::rune_tag >> 32)} {
    }

    explicit inline constexpr Rune(rune ch) noexcept
        : T{ch, int32_t(impl::rune_tag >> 32)} {
    }

    /*
    inline constexpr Rune(const Rune & other) = default;
    inline constexpr Rune & operator=(const Rune & other) = default;
    inline ~Rune() = default;
    */
    
    inline constexpr rune val() const noexcept {
        return i;
    }

    inline utf8_t utf8() const noexcept {
        return utf8_t(i);
    }

    inline constexpr type_id type() const noexcept {
        return rune_id;
    }

    enum {
        static_type = rune_id,
    };
    
    Rune & operator=(rune ch) noexcept {
        return (*this) = Rune{ch};
    }
};

#endif // CRYSP_RUNE_HPP
