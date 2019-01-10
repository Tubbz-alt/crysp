#ifndef CRYSP_CONS_HPP
#define CRYSP_CONS_HPP

#include "t.hpp"

class Cons : public T {
private:
    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits >> 52) == (impl::cons_tag >> 52) &&
            (bits & 0xF) == (impl::cons_tag & 0xF);
    }

protected:
    explicit inline constexpr Cons(uint64_t bits) noexcept : T(bits) {
    }
    
public:

    /*
    inline constexpr Cons(const Cons & other) = default;
    inline constexpr Cons & operator=(const Cons & other) = default;
    inline ~Cons() = default;
    */

    type_id constexpr type() const noexcept {
        return cons_id;
    }
};

#endif // CRYSP_CONS_HPP
