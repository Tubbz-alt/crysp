#ifndef CRYSP_PAIR_HPP
#define CRYSP_PAIR_HPP

#include "t.hpp"
#include "type.hpp"

CRYSP_NS_START

class Pair : public T {
private:
    struct pair {
        T first;
        T rest;
    };
    
    template<class E> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits & impl::pointer_mask) == impl::pair_tag;
    }

protected:
    struct bits_constructor {};
    
    /* needed by subclass constructor Nil() */
    explicit inline constexpr Pair(uint64_t bits,
                                   bits_constructor) noexcept
        : T(bits) {
    }
    
public:
    explicit Pair(T first = T{}, T rest = T{}); /* throw(std::bad_alloc) */
        
    /*
    inline constexpr Pair(const Pair & other) = default;
    inline constexpr Pair & operator=(const Pair & other) = default;
    inline ~Pair() = default;
    */

    static inline constexpr Type type() noexcept {
        return Type{type::pair_id};
    }

    static inline constexpr type::id type_id() noexcept {
        return type::pair_id;
    }

    enum {
          static_type_id = type::pair_id,
    };

    int print(FILE *out) const;
    
    pair * operator->() {
        return reinterpret_cast<pair *>(addr());
    }

    const pair * operator->() const {
        return reinterpret_cast<const pair *>(addr());
    }
};

inline Pair pair(T first, T rest) {
    return Pair{first, rest};
}       

inline T first(Pair x) {
    return x->first;
}

inline T rest(Pair x) {
    return x->rest;
}

CRYSP_NS_END

#endif // CRYSP_PAIR_HPP
