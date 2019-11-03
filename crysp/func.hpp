#ifndef CRYSP_FUNC_HPP
#define CRYSP_FUNC_HPP

#include "array.hpp"
#include "nil.hpp"
#include "slice.hpp"
#include "t.hpp"
#include "type.hpp"
#include "values.hpp"

CRYSP_NS_START

// function wrapper. Can call a function with arbitrary prototype
class Func : public T {
public:
    enum : size_t {
          MaxArg = 15, // support up to 15 function arguments
          MaxRet = 15, // support up to 15 return values
    };

    struct Ret : public DynArray<T, MaxRet> {

        inline constexpr Ret() noexcept
        : DynArray<T, MaxRet>{0}
        { }
    };

private:
    template<class E> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits & impl::pointer_mask) == impl::func_tag;
    }

    struct func {
        void * fun;
        uint16_t retsize, argsize;
	type::id argtype[MaxArg];

        template<class... Args>
        explicit inline constexpr func(void (*f)(Args...))
            : fun{(void *)f}
            , retsize{0}
            , argsize{sizeof...(Args)}
            , argtype{type::id(Args::static_type_id)...}
        { }

        template<class R, class... Args>
        explicit inline constexpr func(R (*f)(Args...))
            : fun{(void *)f}
            , retsize{1}
            , argsize{sizeof...(Args)}
            , argtype{type::id(Args::static_type_id)...}
        {
            static_assert(std::is_base_of<T, R>::value,
                          "Func: single-return function must return T or a subclass");
        }

        template<class... Rs, class... Args>
        explicit inline constexpr func(Values<Rs...> (*f)(Args...))
            : fun{(void *)f}
            , retsize{sizeof...(Rs)}
            , argsize{sizeof...(Args)}
            , argtype{type::id(Args::static_type_id)...}
        { }
    };

    static void callx(Ret & ret, const func * x, const T args[MaxArg]);
    static void call2(Ret & ret, void * fun, const T args[MaxArg]);
    static void calln(Ret & ret, void * fun, const T args[MaxArg]);

public:

    template<class R, class... Args>
    explicit inline Func(R (*f)(Args...)) /* throw(std::bad_alloc) */
        : T{impl::func_tag | GCRYSP_NEW(func, f)} {
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
    Ret operator()(Args&& ... args) {
        enum : size_t { N = sizeof...(Args) };
        static_assert(size_t(N) <= size_t(MaxArg),
                      "Func supports only up to 15 function call arguments");
        func * x = reinterpret_cast<func *>(addr());
        const size_t n = x->argsize;
        if (N != n) {
            impl::throw_out_of_range("wrong argument count in Func call");
        }
        const T vargs[MaxArg] = {std::forward<T>(args)...};
	Ret ret;
        callx(ret, x, vargs);
	return ret;
    }

    Ret call(ConstSlice<T> args);
};

CRYSP_NS_END

#endif // CRYSP_FUNC_HPP
