#ifndef CRYSP_STRING_HPP
#define CRYSP_STRING_HPP

#include "long.hpp"
#include "t.hpp"
#include "type.hpp"

CRYSP_NS_START

namespace impl {
    struct string {
        Long size;
        char data[0];
    };
};

class String : public T {
private:
    using string = CRYSP_NS impl::string;

    template<class E> friend bool is(T arg);

    static inline constexpr bool typecheck(uint64_t bits) noexcept {
        return (bits & impl::pointer_mask) == impl::vector_tag;
    }

public:
    explicit String(Long size = Long{0},
                    const char data[] = nullptr); /* throw(std::bad_alloc) */

    template<size_t N>
    explicit String(const char (&data)[N]) /* throw(std::bad_alloc) */
        : String(Long{N-1, check_overflow}, data) {
    }
    
    /*
    inline constexpr String(const String & other) = default;
    inline constexpr String & operator=(const String & other) = default;
    inline ~String() = default;
    */

    static inline constexpr Type type() noexcept {
        return Type{type::vector_id};
    }

    static inline constexpr type::id type_id() noexcept {
        return type::vector_id;
    }

    enum {
          static_type_id = type::vector_id,
    };

    int print(FILE *out) const;

    Long size() const {
        const string * s = reinterpret_cast<const string *>(addr());
        return s->size;
    };

    // direct access to garbage collected array. use with care!
    const char * data() const {
        const string * s = reinterpret_cast<const string *>(addr());
        return s->data;
    };

    char operator[](Long index) const;
};

CRYSP_NS_END

#endif // CRYSP_STRING_HPP
