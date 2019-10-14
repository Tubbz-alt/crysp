#ifndef CRYSP_SLICE_HPP
#define CRYSP_SLICE_HPP

#include <cassert>
#include <type_traits>

#include "t.hpp"

CRYSP_NS_START

/**
 * ConstSlice is a readonly reference to a contiguous array of crysp::T or derived
 */
template<class E>
class ConstSlice {
    static_assert(std::is_base_of<T, E>::value,
                  "ConstSlice element type must extend T");
protected:
    size_t sz;
    const E * v;

public:
    inline constexpr ConstSlice() noexcept
    : sz{0}, v{nullptr} {
    }
    
    inline constexpr ConstSlice(size_t size, const E * address) noexcept
        : sz{size}, v{address}
    { }

    inline constexpr E * data() const noexcept {
        return v;
    }
    
    inline constexpr size_t size() const noexcept {
        return sz;
    }

    inline constexpr E operator[](size_t index) const {
        assert(index < sz);
        return v[index];
    }

    inline constexpr ConstSlice<E> slice(size_t start, size_t end) const {
        assert(start <= end);
        assert(end <= sz);
        return ConstSlice<E>{end - start, v + start};
    }
};

/**
 * Slice is a reference to a contiguous array of crysp::T or derived
 */
template<class E>
class Slice : public ConstSlice<E> {

private:
    using Base = ConstSlice<E>;

public:
    inline constexpr Slice() noexcept
    : Base{} {
    }
    
    inline constexpr Slice(size_t size, E * address) noexcept
        : Base{size, address}
    { }

    using Base::data;
    using Base::size;
    using Base::operator[];

    inline constexpr E * data() noexcept {
        return const_cast<E *>(Base::v);
    }
    
    inline constexpr E & operator[](size_t index) {
        assert(index < Base::sz);
        return data()[index];
    }

    inline constexpr Slice<E> slice(size_t start, size_t end) {
        assert(start <= end);
        assert(end <= Base::sz);
        return Slice<E>{end - start, data() + start};
    }
};

CRYSP_NS_END

#endif // CRYSP_SLICE_HPP
