#ifndef CRYSP_TYPE_HPP
#define CRYSP_TYPE_HPP

#include "t.hpp"

CRYSP_NS_START

class Type : public T {
private:
    template<class E> friend bool is(T arg);

    // needed by friend is()
    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits >> 48) == (impl::type_tag >> 48);
    }

public:
    inline constexpr Type() noexcept
    /**/: T{int32_t(type::t_id), uint32_t(impl::type_tag >> 32)} {
    }

    explicit inline constexpr Type(type::id id) noexcept
        : T{int32_t(id), uint32_t(impl::type_tag >> 32)} {
    }

    /*
    inline constexpr Type(const Type & other) = default;
    inline constexpr Type & operator=(const Type & other) = default;
    inline ~Type() = default;
    */
    
    // type of this object. overloads T::type()
    inline constexpr Type type() const noexcept {
        return Type{type::type_id};
    }

    // type_id of this object. overloads T::type_id()
    inline constexpr type::id type_id() const noexcept {
        return type::type_id;
    }

    enum {
          static_type_id = type::type_id,
    };
    
    // return number of written bytes
    int print(FILE *out) const;

    inline constexpr type::id id() const noexcept {
        return type::id(i);
    }

    const char * name() const noexcept;
};

// declared in t.hpp
inline constexpr Type T::type() const noexcept {
    return Type{type_id()};
}

CRYSP_NS_END

#endif // CRYSP_TYPE_HPP
