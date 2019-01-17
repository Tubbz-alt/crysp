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

    // defined in type.hpp
    inline constexpr Type type() const noexcept;

    inline constexpr type::id type_id() const noexcept {
        return type::pair_id;
    }

    enum {
          static_type_id = type::pair_id,
    };

    int print(FILE *out) const;
    
    pair * operator->() {
        return (pair *)addr();
    }

    const pair * operator->() const {
        return (const pair *)addr();
    }
};

#endif // CRYSP_PAIR_HPP
