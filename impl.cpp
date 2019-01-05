
#include "fixnum.hpp"
#include "int.hpp"
#include "nil.hpp"

const Null nil;

const Fixnum most_positive_fixnum(0x7fffffffffffll);
const Fixnum most_negative_fixnum(-0x800000000001ll);

const Int most_positive_int(0x7fffffff);
const Int most_negative_int(-0x80000000);

void Fixnum::fixnum_range_error() /* throw(std::range_error) */ {

    throw std::range_error{"not a fixnum"};
}
