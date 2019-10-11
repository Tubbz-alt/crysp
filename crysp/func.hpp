#ifndef CRYSP_FUNC_HPP
#define CRYSP_FUNC_HPP

#include <functional>  // std::bad_function_call
#include <stdexcept>   // std::out_of_range
#include <vector>

#include "new.hpp"
#include "t.hpp"
#include "type.hpp"

CRYSP_NS_START

class Func : public T {
private:
    struct func {
        void (*fun)();
        size_t narg;
    };

    template<class To> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits & impl::pointer_mask) == impl::func_tag;
    }

public:
    explicit inline Func(void (*f)()) /* throw(std::bad_alloc) */
        : T{impl::func_tag | GCRYSP_NEW(func, f, 0)} {
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

    std::vector<T> call(const std::vector<T>& vargs) {
        func * x = reinterpret_cast<func *>(addr());
        if (vargs.size() != x->narg) {
	   impl::throw_out_of_range("wrong number of arguments in Func call");
        }
        x->fun();
        return std::vector<T>{};
    }
    
};

CRYSP_NS_END

#endif // CRYSP_FUNC_HPP
