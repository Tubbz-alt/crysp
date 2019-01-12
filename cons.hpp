#ifndef CRYSP_CONS_HPP
#define CRYSP_CONS_HPP

#include "t.hpp"
#include "new.hpp"

class Cons : public T {
private:
    struct cons {
        T first, rest;
    };
    
    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits >> 52) == (impl::cons_tag >> 52) &&
            (bits & 0xF) == (impl::cons_tag & 0xF);
    }

protected:
    struct bits_constructor {};
    
    /* needed by subclass constructor Nil() */
    explicit inline constexpr Cons(uint64_t bits, bits_constructor) noexcept : T(bits) {
    }
    
public:
    explicit inline Cons(T first = T{impl::nil_bits},
                         T rest  = T{impl::nil_bits}) /* throw(std::bad_alloc) */
        : T(impl::cons_tag | GCRYSP_NEW(cons, first, rest)) {
    }
        
    /*
    inline constexpr Cons(const Cons & other) = default;
    inline constexpr Cons & operator=(const Cons & other) = default;
    inline ~Cons() = default;
    */

    type_id constexpr type() const noexcept {
        return cons_id;
    }

    cons * operator->() {
        return (cons *)addr();
    }
};

#endif // CRYSP_CONS_HPP
