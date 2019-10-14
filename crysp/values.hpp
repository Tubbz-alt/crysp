#ifndef CRYSP_VALUES_HPP
#define CRYSP_VALUES_HPP

#include "t.hpp"

CRYSP_NS_START

namespace impl {

    // extract the n-th type from Args
    template<size_t N, class... Args>
    struct nth_type_struct {
    };

    template<size_t N, class Arg0, class... Args>
    struct nth_type_struct<N, Arg0, Args...> {
        using type = typename nth_type_struct<N-1, Args...>::type;
    };

    template<class Arg0, class... Args>
    struct nth_type_struct<0, Arg0, Args...> {
        using type = Arg0;
    };
}

// extract the N-th type from Args
template<size_t N, class... Args>
using nth_type = typename impl::nth_type_struct<N, Args...>::type;

/**
 * Values represent multiple values, for example returned by a function.
 *
 * It is similar in spirit to std:tuple, the main difference being
 * that Values can only hold objects derived from crysp::T
 *
 * Note that Values is (almost) a plain struct:
 * it does NOT derive from crysp::T
 */
template<class... Args>
class Values {
private:
    T v[sizeof...(Args)];

public:
    explicit inline constexpr Values(Args... args) noexcept
        : v{args...}
    { }
        
    enum { Size = sizeof...(Args) };

    static inline constexpr size_t size() noexcept {
        return Size;
    }

    template <size_t N>
    inline constexpr nth_type<N, Args...> get() const noexcept {
        return static_cast<const nth_type<N, Args...>&>(v[N]);
    }

    template <size_t N>
    inline constexpr void set(nth_type<N, Args...> arg) noexcept {
        v[N] = arg;
    }
};

template<class... Args>
inline constexpr Values<Args...> values(Args... args) noexcept {
    return Values<Args...>{args...};
}

CRYSP_NS_END

#endif // CRYSP_VALUES_HPP
