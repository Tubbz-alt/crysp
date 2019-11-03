#include "crysp/long.hpp"

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

CRYSP_NOINLINE Long f01() {
    return Long{7};
}

CRYSP_NOINLINE Long f11(Long a) {
    return -a;
}

CRYSP_NOINLINE Long f21(Long a, Long b) {
    return a | b;
}

CRYSP_NOINLINE Long f31(Long a, Long b, Long c) {
    return a | b | c;
}

CRYSP_NOINLINE Long f41(Long a, Long b, Long c, Long d) {
    return a | b | c | d;
}

CRYSP_NOINLINE Long f51(Long a, Long b, Long c, Long d, Long e) {
    return a | b | c | d | e;
}

CRYSP_NOINLINE Long f61(Long a, Long b, Long c, Long d, Long e, Long f) {
    return a | b | c | d | e | f;
}

CRYSP_NOINLINE Long f71(Long a, Long b, Long c, Long d, Long e, Long f, Long g) {
    return a | b | c | d | e | f | g;
}

CRYSP_NOINLINE Long f81(Long a, Long b, Long c, Long d, Long e, Long f, Long g, Long h) {
    return a | b | c | d | e | f | g | h;
}

CRYSP_NOINLINE Long f91(Long a, Long b, Long c, Long d, Long e, Long f, Long g, Long h,
                        Long i) {
    return a | b | c | d | e | f | g | h | i;
}

CRYSP_NOINLINE Long fa1(Long a, Long b, Long c, Long d, Long e, Long f, Long g, Long h,
                        Long i, Long j) {
    return a | b | c | d | e | f | g | h | i | j;
}

CRYSP_NOINLINE Long fb1(Long a, Long b, Long c, Long d, Long e, Long f, Long g, Long h,
                        Long i, Long j, Long k) {
    return a | b | c | d | e | f | g | h | i | j | k;
}

CRYSP_NOINLINE Long fc1(Long a, Long b, Long c, Long d, Long e, Long f, Long g, Long h,
                        Long i, Long j, Long k, Long l) {
    return a | b | c | d | e | f | g | h | i | j | k | l;
}

CRYSP_NOINLINE Long fd1(Long a, Long b, Long c, Long d, Long e, Long f, Long g, Long h,
                        Long i, Long j, Long k, Long l, Long m) {
    return a | b | c | d | e | f | g | h | i | j | k | l | m;
}


template<size_t N>
struct LongV {
    Long v[N];
};

CRYSP_NOINLINE LongV<2> f02() {
    return LongV<2>{Long{7}, Long{8}};
}

CRYSP_NOINLINE LongV<3> f03() {
    return LongV<3>{Long{7}, Long{8}, Long{9}};
}

CRYSP_NOINLINE LongV<4> f04() {
    return LongV<4>{Long{7}, Long{8}, Long{9}, Long{10}};
}

CRYSP_NOINLINE LongV<5> f05() {
    return LongV<5>{Long{7}, Long{8}, Long{9}, Long{10}, Long{11}};
}

CRYSP_NOINLINE LongV<6> f66(Long a, Long b, Long c, Long d, Long e, Long f) {
    return LongV<6>{a, b, c, d, e, f};
}

