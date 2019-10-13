#include "func.hpp"

CRYSP_NS_START

std::vector<T> Func::call(const std::vector<T>& vargs) {
    func * x = reinterpret_cast<func *>(addr());
    if (vargs.size() != x->argcount) {
        impl::throw_out_of_range("wrong number of arguments in Func call");
    }
    x->fun(nil, nil, nil, nil,
           nil, nil, nil, nil,
           nil, nil, nil, nil,
           nil, nil, nil, nil);
    return std::vector<T>{};
}

CRYSP_NS_END
