#ifndef CRYSP_PAIR_HPP
#define CRYSP_PAIR_HPP

#include "t.hpp"
#include "new.hpp"

class Pair : public T {
private:
    struct pair {
        T first, second;
    };
    
    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits & impl::pointer_mask) == impl::pair_tag;
    }

protected:
    struct bits_constructor {};
    
    /* needed by subclass constructor Nil() */
    explicit inline constexpr Pair(uint64_t bits, bits_constructor) noexcept : T(bits) {
    }
    
public:
    explicit inline Pair(T first  = T{impl::nil_bits},
                         T second = T{impl::nil_bits}) /* throw(std::bad_alloc) */
        : T(impl::pair_tag | GCRYSP_NEW(pair, first, second)) {
    }
        
    /*
    inline constexpr Pair(const Pair & other) = default;
    inline constexpr Pair & operator=(const Pair & other) = default;
    inline ~Pair() = default;
    */

    type_id constexpr type() const noexcept {
        return pair_id;
    }

    pair * operator->() {
        return (pair *)addr();
    }
};

#endif // CRYSP_PAIR_HPP
