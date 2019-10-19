#include "func.hpp"
#include "nil.hpp"
#include "values.hpp"

CRYSP_NS_START

Func::Ret Func::call(ConstSlice<T> args) {
    func * x = reinterpret_cast<func *>(addr());
    const size_t n = x->argsize;
    if (args.size() != n) {
        impl::throw_out_of_range("wrong argument count in Func call");
    }
    T vargs[MaxArg];
    for (size_t i = 0; i < n; i++) {
        vargs[i] = args[i];
    }
    Ret ret;
    callx(ret, x, vargs);
    return ret;
}

void Func::callx(Ret & ret, const func * x, const T args[MaxArg]) {
    const size_t argsize = x->argsize;
    for (size_t i = 0; i < argsize; i++) {
        T arg = args[i];
        type::id expected_type_id = x->argtype[i];
        if (expected_type_id == type::id::t_id) {
            // argument can be any type
            continue;
        }
        if (expected_type_id != arg.type_id()) {
            // TODO: support subclasses
            impl::throw_runtime_error("wrong argument type in Func call");
        }
    }
    // at least on x86_64 and arm64, function returning up to two values
    // (each as wide as T) return them in registers.
    //
    // function returning more than two values have instead different ABI:
    // they receive a hidden first argument containing the base address
    // where to store the return values.
    if (ret.resize(x->retsize) <= 2) {
        call2(ret, x->fun, args);
    } else {
        calln(ret, x->fun, args);
    }
}

void Func::call2(Ret & ret, void * fun, const T args[MaxArg]) {

    // same ABI as function returning zero, one or two values
    // at least on x86_64 and arm64
    using f_type = Array<T, 2> (*)(T, T, T, T, T,
                                   T, T, T, T, T,
                                   T, T, T, T, T);
    f_type f = reinterpret_cast<f_type>(fun);
    auto vret = f(args[0], args[1], args[2], args[3], args[4],
                  args[5], args[6], args[7], args[8], args[9],
                  args[10],args[11],args[12],args[13],args[14]);
    for (size_t i = 0, n = ret.size(); i < n; i++) {
        ret[i] = vret[i];
    }
}

void Func::calln(Ret & ret, void * fun, const T args[MaxArg]) {

    // same ABI as function returning three or more values
    // at least on x86_64 and arm64
    using f_type = Array<T, MaxRet> (*)(T, T, T, T, T,
                                        T, T, T, T, T,
                                        T, T, T, T, T);
    f_type f = reinterpret_cast<f_type>(fun);
    auto vret = f(args[0], args[1], args[2], args[3], args[4],
                  args[5], args[6], args[7], args[8], args[9],
                  args[10],args[11],args[12],args[13],args[14]);
    for (size_t i = 0, n = ret.size(); i < n; i++) {
        ret[i] = vret[i];
    }
}


CRYSP_NS_END
