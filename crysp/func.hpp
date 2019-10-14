#ifndef CRYSP_FUNC_HPP
#define CRYSP_FUNC_HPP

#include "t.hpp"
#include "nil.hpp"
#include "type.hpp"
#include "slice.hpp"

CRYSP_NS_START

class Func : public T {
public:
    enum : size_t {
          MaxArg = 15, // support up to 15 function arguments
          MaxRet = 15, // support up to 15 return values
    };

    struct Ret {
        size_t size;
        T val[MaxRet];

        inline constexpr Ret() noexcept
        : size{0}, val{nil, nil, nil, nil, nil,
                       nil, nil, nil, nil, nil,
                       nil, nil, nil, nil, nil}
        { }
    };

private:
    struct func {
        void * fun;
        uint16_t retsize, argsize;
	type::id argtype[MaxArg];
    };

    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits & impl::pointer_mask) == impl::func_tag;
    }

    static void call_impl(Ret & ret, const func * x, const T args[MaxArg]);
    static void call0(T ret[MaxRet], void * fun, const T args[MaxArg]);
    static void call1(T ret[MaxRet], void * fun, const T args[MaxArg]);
    static void call2(T ret[MaxRet], void * fun, const T args[MaxArg]);
    static void calln(size_t retsize, T ret[MaxRet], void * fun, const T args[MaxArg]);
    
public:

    explicit inline Func(void (*f)()) /* throw(std::bad_alloc) */
        : T{impl::func_tag | GCRYSP_NEW(func, (void *)f, uint16_t(0), uint16_t(0), {})} {
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
        call_impl(ret, x, vargs);
        return ret;
    }

    Ret call(ConstSlice<T> args);
};

CRYSP_NS_END

#endif // CRYSP_FUNC_HPP
