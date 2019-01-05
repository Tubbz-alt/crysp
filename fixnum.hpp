#ifndef CRYSP_FIXNUM_HPP
#define CRYSP_FIXNUM_HPP

#include <stdexcept>

#include "t.hpp"

class Fixnum : public T {
private:
    enum {
        fixnum_sign  = 0x0000800000000000ull,
    };

    static void fixnum_range_error(); /* throw(std::range_error) */
    
    static inline uint64_t tag(int64_t i) /* throw(std::range_error) */ {
        uint64_t n = uint64_t(i), u = n & ~impl::tag_mask;
        if (u != n && (~n & impl::tag_mask) != 0) {
            fixnum_range_error();
        }
        return u | impl::fixnum_tag;
    }

    static inline constexpr int64_t untag(uint64_t bits) noexcept {
        bits &= ~impl::tag_mask;
        return bits | -(bits & fixnum_sign);
    }

protected:
    explicit inline Fixnum(int32_t i, uint32_t tag) noexcept
        : T(i, tag) {
    }
        
    
public:
    inline constexpr Fixnum() noexcept
    /**/: T(uint64_t(impl::fixnum_tag)) {
    }

    explicit inline Fixnum(int64_t i) /* throw(std::range_error) */
        : T(tag(i)) {
    }

    /*
    inline constexpr Fixnum(const Fixnum & other) = default;
    inline constexpr Fixnum & operator=(const Fixnum & other) = default;
    inline ~Fixnum() = default;
    */
    
    inline operator bool() const noexcept {
	return true;
    }

    inline operator int64_t() const noexcept {
	return untag(bits);
    }

    inline int64_t value() const noexcept {
        return untag(bits);
    }

    /* assignment. needed because constructor Fixnum(int64_t) is explicit */
    inline Fixnum & operator=(int64_t i) /* throw(std::range_error) */ {
        (*this) = Fixnum(i);
        return *this;
    }
};

extern const Fixnum most_positive_fixnum, most_negative_fixnum;

#endif // CRYSP_FIXNUM_HPP
