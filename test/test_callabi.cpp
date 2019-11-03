#include "crysp/fixnum.hpp"

CRYSP_NS_USE

/**
 * x86_64 function call ABI:
 * arguments, each up to sizeof(void*):
 *   %rdi, %rsi, %rdx, %rcx, %r8, %r9,
 *   then read from stack at 0x8(%rsp) and up
 * return value:
 *   up to 2*sizeof(void): store in %rax, %rdx
 *   3*sizeof(void) or more: store in memory at (%rdi) and up,
 *     i.e. at address pointed by hidden first parameter,
 *     and before returning copy %rdi to %rax
 */


/**
 * arm64 function call ABI:
 * arguments, each up to sizeof(void*):
 *   x0, x1, x2, x3, x4, x5, x6, x7,
 *   then read from stack at [sp] and up
 * return value:
 *   up to 2*sizeof(void): store in x0, x1
 *   3*sizeof(void) or more: store in memory at [x8] and up
 */

CRYSP_NOINLINE Fixnum f01() {
    return Fixnum{7};
}

CRYSP_NOINLINE Fixnum f11(Fixnum a) {
    return -a;
}

CRYSP_NOINLINE Fixnum f21(Fixnum a, Fixnum b) {
    return a | b;
}

CRYSP_NOINLINE Fixnum f31(Fixnum a, Fixnum b, Fixnum c) {
    return a | b | c;
}

CRYSP_NOINLINE Fixnum f41(Fixnum a, Fixnum b, Fixnum c, Fixnum d) {
    return a | b | c | d;
}

CRYSP_NOINLINE Fixnum f51(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e) {
    return a | b | c | d | e;
}

CRYSP_NOINLINE Fixnum f61(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f) {
    return a | b | c | d | e | f;
}

CRYSP_NOINLINE Fixnum f71(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f, Fixnum g) {
    return a | b | c | d | e | f | g;
}

CRYSP_NOINLINE Fixnum f81(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f, Fixnum g, Fixnum h) {
    return a | b | c | d | e | f | g | h;
}

CRYSP_NOINLINE Fixnum f91(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f, Fixnum g, Fixnum h,
                        Fixnum i) {
    return a | b | c | d | e | f | g | h | i;
}

CRYSP_NOINLINE Fixnum fa1(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f, Fixnum g, Fixnum h,
                        Fixnum i, Fixnum j) {
    return a | b | c | d | e | f | g | h | i | j;
}

CRYSP_NOINLINE Fixnum fb1(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f, Fixnum g, Fixnum h,
                        Fixnum i, Fixnum j, Fixnum k) {
    return a | b | c | d | e | f | g | h | i | j | k;
}

CRYSP_NOINLINE Fixnum fc1(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f, Fixnum g, Fixnum h,
                        Fixnum i, Fixnum j, Fixnum k, Fixnum l) {
    return a | b | c | d | e | f | g | h | i | j | k | l;
}

CRYSP_NOINLINE Fixnum fd1(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f, Fixnum g, Fixnum h,
                        Fixnum i, Fixnum j, Fixnum k, Fixnum l, Fixnum m) {
    return a | b | c | d | e | f | g | h | i | j | k | l | m;
}


template<size_t N>
struct FixnumV {
    Fixnum v[N];
};

CRYSP_NOINLINE FixnumV<2> f02() {
    return FixnumV<2>{Fixnum{7}, Fixnum{8}};
}

CRYSP_NOINLINE FixnumV<3> f03() {
    return FixnumV<3>{Fixnum{7}, Fixnum{8}, Fixnum{9}};
}

CRYSP_NOINLINE FixnumV<4> f04() {
    return FixnumV<4>{Fixnum{7}, Fixnum{8}, Fixnum{9}, Fixnum{10}};
}

CRYSP_NOINLINE FixnumV<5> f05() {
    return FixnumV<5>{Fixnum{7}, Fixnum{8}, Fixnum{9}, Fixnum{10}, Fixnum{11}};
}

CRYSP_NOINLINE FixnumV<6> f66(Fixnum a, Fixnum b, Fixnum c, Fixnum d, Fixnum e, Fixnum f) {
    return FixnumV<6>{a, b, c, d, e, f};
}

