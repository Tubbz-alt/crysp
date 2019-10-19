#ifndef CRYSP_ARRAY_HPP
#define CRYSP_ARRAY_HPP

#include <array>
#include <cassert>

#include "impl.hpp" // CRYSP_NS_START

CRYSP_NS_START

// Array with fixed size.
// it is an alias for std::array
template<class E, size_t N>
using Array = std::array<E, N>;

// Array with fixed maximum size.
// Does NOT extend T.
template<class E, size_t MaxN>
class DynArray : public Array<E, MaxN> {
private:
    size_t sz;

    using Base = Array<E, MaxN>;
    
public:
    template<class... Args>
    explicit inline constexpr DynArray(size_t n, Args... args) 
        : Base{std::forward<E>(args)...}
        , sz{n}
    {
        assert(n <= MaxN);
    }

    /*
    inline constexpr DynArray(const DynArray & other) = default;
    inline constexpr DynArray<E,N> & operator=(const DynArray<E,N> & other) = default;
    inline ~DynArray() = default;
    */

    using element_type = E;
    enum : size_t { static_max_size = MaxN };
          
    static inline constexpr size_t max_size() noexcept {
        return MaxN;
    }

    inline constexpr size_t size() const noexcept {
        return sz;
    }

    inline constexpr size_t resize(size_t new_size) {
        assert(new_size <= MaxN);
        return sz = new_size;
    }
    
}; // class DynArray

CRYSP_NS_END

#endif // CRYSP_ARRAY_HPP
