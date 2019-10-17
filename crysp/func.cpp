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
    return call_impl(x, vargs);
}

Func::Ret Func::call_impl(const func * x, const T args[MaxArg]) {
    const size_t n = x->argsize;
    for (size_t i = 0; i < n; i++) {
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
    Ret ret;
    void * f = x->fun;
    switch ((ret.size = x->retsize)) {
    case 0:
        call0(ret.val, f, args);
        break;
    case 1:
        call1(ret.val, f, args);
        break;
    case 2:
        call2(ret.val, f, args);
        break;
    default:
        calln(ret.size, ret.val, f, args);
        break;
    }
    return ret;
}

void Func::call0(T /*ret*/[MaxRet], void * fun, const T args[MaxArg]) {

    // at least on x86_64 and arm64, we can safely pass to a function
    // more arguments than it expects: extra arguments are just ignored
    using f_type = void (*)(T, T, T, T, T,
                            T, T, T, T, T,
                            T, T, T, T, T);
    f_type f = reinterpret_cast<f_type>(fun);
    f(args[0], args[1], args[2], args[3], args[4],
      args[5], args[6], args[7], args[8], args[9],
      args[10],args[11],args[12],args[13],args[14]);
}

void Func::call1(T ret[MaxRet], void * fun, const T args[MaxArg]) {

    using f_type = T (*)(T, T, T, T, T,
                         T, T, T, T, T,
                         T, T, T, T, T);
    f_type f = reinterpret_cast<f_type>(fun);
    T vret = f(args[0], args[1], args[2], args[3], args[4],
               args[5], args[6], args[7], args[8], args[9],
               args[10],args[11],args[12],args[13],args[14]);
    ret[0] = vret;
}

void Func::call2(T ret[MaxRet], void * fun, const T args[MaxArg]) {

    using f_type = Values<T, T> (*)(T, T, T, T, T,
                                    T, T, T, T, T,
                                    T, T, T, T, T);
    f_type f = reinterpret_cast<f_type>(fun);
    Values<T, T> vret = f(args[0], args[1], args[2], args[3], args[4],
                          args[5], args[6], args[7], args[8], args[9],
                          args[10],args[11],args[12],args[13],args[14]);
    ret[0] = vret.get<0>();
    ret[1] = vret.get<1>();
}

void Func::calln(size_t retsize, T ret[MaxRet], void * fun, const T args[MaxArg]) {

    // approximates Values<T, ...> sufficiently well
    // to have same in-memory layout and same function return ABI
    // at least on x86_64 and arm64
    struct ret_type {
        T val[MaxRet];
    };
    using f_type = ret_type (*)(T, T, T, T, T,
                                T, T, T, T, T,
                                T, T, T, T, T);
    f_type f = reinterpret_cast<f_type>(fun);
    ret_type vret = f(args[0], args[1], args[2], args[3], args[4],
                      args[5], args[6], args[7], args[8], args[9],
                      args[10],args[11],args[12],args[13],args[14]);
    for (size_t i = 0; i < retsize; i++) {
        ret[i] = vret.val[i];
    }
}


CRYSP_NS_END
