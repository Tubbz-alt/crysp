
#include <stdexcept> // std::overflow_error
#include <typeinfo>  // std::bad_cast

#include "fixnum.hpp"

void impl::throw_bad_cast() /* throw(std::bad_cast) */ {
    throw std::bad_cast{};
}

void Fixnum::throw_overflow_error() /* throw(std::overflow_error) */ {
    throw std::overflow_error{"integer too large, overflows Fixnum"};
}
