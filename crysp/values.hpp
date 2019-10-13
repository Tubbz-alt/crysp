#ifndef CRYSP_VALUES_HPP
#define CRYSP_VALUES_HPP

#include <array>

#include "t.hpp"

CRYSP_NS_START

enum {
      MaxValues = 16,
};

namespace impl {
    struct ValuesTls {
        size_t n;
        T v[MaxValues];

        template<class... Args>
        inline constexpr ValuesTls * assign(Args... args) noexcept
        {
            static_assert(sizeof...(Args) <= MaxValues,
                          "Values supports only up to 16 values");
            struct Tn {
                T v[sizeof...(Args)];
            };
            n = sizeof...(Args);
            reinterpret_cast<Tn &>(v) = Tn{args...};
            return this;
        }
    };
    extern thread_local ValuesTls values_tls;
}

/**
 * Values is not a first-class object:
 * it stores its data in a per-thread global variable.
 *
 * It should only be used to return multiple values
 * from a function, which are then immediately copied
 * somewhere else.
 *
 * Do not define variables, fields or arguments with type
 * Values or with a type that uses Values in any way.
 */
template<class... Args>
class Values;

template<>
class Values<> {
public:
    inline constexpr Values() noexcept {
    }
};

template<class Arg0>
class Values<Arg0> {
private:
    T data;

public:
    explicit inline constexpr Values(Arg0 a0) noexcept
        : data{a0} {
    }
};

template<class Arg0, class Arg1>
class Values<Arg0, Arg1> {
    T data[2];

public:
    inline constexpr Values(Arg0 a0, Arg1 a1) noexcept
        : data{a0, a1} {
    }
};

template<class Arg0, class Arg1, class Arg2, class... Args>
class Values<Arg0, Arg1, Arg2, Args...> {
    T v0;
    impl::ValuesTls *data;

public:
    inline constexpr Values(Arg0 a0, Arg1 a1, Arg2 a2, Args... as) noexcept
        : v0{a0}
        , data{impl::values_tls.assign(a0, a1, a2, as...)}
    {
    }
};

template<class... Args>
inline constexpr Values<Args...> values(Args... args) noexcept {
    return Values<Args...>(args...);
}

CRYSP_NS_END

#endif // CRYSP_VALUES_HPP
