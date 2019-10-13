#ifndef CRYSP_FUNC_HPP
#define CRYSP_FUNC_HPP

#include <tuple>
#include <vector>

#include "new.hpp"
#include "nil.hpp"
#include "t.hpp"
#include "type.hpp"
#include "values.hpp"

CRYSP_NS_START

class Func : public T {
private:
    using ret_type = std::tuple<T, T>;
    
    // pretend function pointer accepts 16 arguments
    // and returns two values.
    // this is safe at least on x86_64 and arm64,
    // provided the returned values are used only
    // if the actual function really returns them.
    using func_type = ret_type (*)(T, T, T, T,
                                   T, T, T, T,
                                   T, T, T, T,
                                   T, T, T, T);
    struct func {
        func_type fun;
        uint16_t retcount, argcount;
	type::id argtype[16]; // support up to 16 function arguments
    };

    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits & impl::pointer_mask) == impl::func_tag;
    }

public:
    explicit inline Func(void (*f)()) /* throw(std::bad_alloc) */
        : T{impl::func_tag | GCRYSP_NEW(func, (func_type)f, 0, 0, {})} {
    }

    /*
    inline constexpr Func(const Func & other) = default;
    inline constexpr Func & operator=(const Func & other) = default;
    inline ~Func() = default;
    */

    static inline constexpr Type type() noexcept {
        return Type{type::func_id};
    }

    static inline constexpr type::id type_id() noexcept {
        return type::func_id;
    }

    enum {
          static_type_id = type::func_id,
    };

    // int print(FILE *out) const;

    template<class ...Args>
    std::vector<T> operator()(Args&& ... args) {
        /*
        static_assert(is_derived_from_T<Args>::value && ...,
                      "each argument must have type T or a subclass");
        */
        std::vector<T> vargs{std::forward<T>(args)...};
        return call(vargs);
    }

    std::vector<T> call(const std::vector<T>& vargs);
    
};

CRYSP_NS_END

#endif // CRYSP_FUNC_HPP
