#ifndef CRYSP_FIXNUM_HPP
#define CRYSP_FIXNUM_HPP

#include "t.hpp"

class Fixnum : public T {
private:
    friend class T;
    
    static void fixnum_range_error(); /* throw(std::range_error) */
    
    static inline uint64_t tag(int64_t i) /* throw(std::range_error) */ {
        uint32_t hi = uint64_t(i) >> 50;
        if (hi != 0 && hi != 0x3FFF) {
            fixnum_range_error();
        }
        return (uint64_t(i) & ~impl::fixnum_mask) | impl::fixnum_tag;
    }

    static inline constexpr int64_t untag(uint64_t bits) noexcept {
        return int64_t(bits << 14) >> 14;
    }

protected:
    /* needed by subclass constructor Int(int32_t) */
    inline constexpr Fixnum(int32_t i, uint32_t tag) noexcept
    /**/ : T{uint64_t(int64_t(i)) | (uint64_t(tag) << 32)} {
    }
        
    
public:
    inline constexpr Fixnum() noexcept
    /**/ : T{uint64_t(impl::fixnum_tag)} {
    }

    /* may throw: Fixnum only holds 50 bits */
    explicit inline Fixnum(int64_t i) /* throw(std::range_error) */
    /**/ : T{tag(i)} {
    }

    /*
    inline constexpr Fixnum(const Fixnum & other) = default;
    inline constexpr Fixnum & operator=(const Fixnum & other) = default;
    inline ~Fixnum() = default;
    */
    
    inline int64_t val() const noexcept {
        return untag(bits);
    }

    /* may throw: Fixnum only holds 50 bits */
    inline Fixnum & operator=(int64_t i) /* throw(std::range_error) */ {
        return (*this) = Fixnum{i};
    }
};

extern const Fixnum most_positive_fixnum, most_negative_fixnum;

#endif // CRYSP_FIXNUM_HPP
