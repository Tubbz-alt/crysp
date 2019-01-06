#include <cstdio>

#include "nil.hpp"
#include "double.hpp"
#include "test.hpp"
#include "fixnum.hpp"
#include "float.hpp"
#include "int.hpp"


noinline noinline void show(T x) {
    printf("%016lX = ", x.debug_bits());
    x.print(stdout);
    putchar('\n');
}

noinline void test_bool() {
    show(nil);
    show(t);
}

noinline void test_double() {
    show(Double{0.0});
    show(Double{0.5});
    show(Double{1.0});
    show(Double{1023.0});
    show(Double{1.0/0.0}); // inf
    show(Double{-0.0/0.0}); // -NaN
}

noinline void test_float() {
    show(Float{0.0f});
    show(Float{0.5f});
    show(Float{1.0f});
    show(Float{1023.0f});
    show(Float{1.0f/0.0f}); // inf
    show(Float{-0.0f/0.0f}); // -NaN
}

noinline void test_fixnum_assign() {
    Fixnum n;
    TEST_EQ(n.val(), 0);
    TEST_EQ(n, Int{});
    for (int32_t i = -16; i <= 16; i++) {
        n = i;
        TEST_EQ(n.val(), i);
        TEST_EQ(n, Int{i});
        if (n.val() >= -1 && n.val() <= 1)
            show(n);
    }
    show(most_positive_fixnum);
    show(most_negative_fixnum);
    show(most_positive_int);
    show(most_negative_int);
}

int64_t mod_fixnum(int64_t i) {
    i &= 0x3FFFFFFFFFFFFll;
    return (i << 14) >> 14; // sign extend
}
 
noinline void test_fixnum_unary_op() {
    Fixnum n;
    // test ++ and --
    for (int32_t i = -16; i <= 16; i++) {
        n = i;
        n++; TEST_EQ(n.val(), i + 1);
        ++n; TEST_EQ(n.val(), i + 2);
        n--; TEST_EQ(n.val(), i + 1);
        --n; TEST_EQ(n.val(), i + 0);
    }
    // test overflow and underflow
    int64_t lo = most_negative_fixnum.val();
    int64_t hi = most_positive_fixnum.val();
    n = hi;
    n++; TEST_EQ(n.val(), lo);
    n--; TEST_EQ(n.val(), hi);
    ++n; TEST_EQ(n.val(), lo);
    --n; TEST_EQ(n.val(), hi);

    // test += and -=
    for (int32_t i = -16; i <= 16; i++) {
        for (int32_t j = -16; j <= 16; j++) {
            n = i;
            n += Fixnum{j}; TEST_EQ(n.val(), i + j);
            n -= Fixnum{i}; TEST_EQ(n.val(), j);
        }
    }

    // test overflow and underflow
    for (int32_t i = -16; i <= 0; i++) {
        for (int32_t j = -32; j <= 32; j++) {
            n = hi - i;
            n += Fixnum{j}; TEST_EQ(n.val(), mod_fixnum(hi - i + j));
            n -= Fixnum{j}; TEST_EQ(n.val(), mod_fixnum(hi - i));
        }
    }

    // test unary + - !
    for (int32_t i = -16; i <= 16; i++) {
        n = i;
        n = +n; TEST_EQ(n.val(), +i);
        n = -n; TEST_EQ(n.val(), -i);
        n = !n; TEST_EQ(n.val(), !-i);
    }
    // test overflow and underflow
    for (int32_t i = 0; i <= 16; i++) {
        n = hi - i;
        n = -n; TEST_EQ(n.val(), -hi + i);

        n = lo + i;
        n = -n; TEST_EQ(n.val(), mod_fixnum(-lo - i));
    }
}

noinline void test_fixnum_binary_op() {
    Fixnum a, b, c;

    int64_t lo = most_negative_fixnum.val();
    int64_t hi = most_positive_fixnum.val();

    for (int64_t i = -50; i <= 50; i++) {
        for (int64_t j = -50; j <= 50; j++) {
            a = i;
            b = j;

            TEST_EQ(a < b, i < j);
            
            c = a + b; TEST_EQ(c.val(), i + j);
            c = a - b; TEST_EQ(c.val(), i - j);
            c = a & b; TEST_EQ(c.val(), i & j);
            c = a | b; TEST_EQ(c.val(), i | j);
            c = a ^ b; TEST_EQ(c.val(), i ^ j);

            if (j >= 0) {
                uint8_t n = uint8_t(j);
                c = a << n; TEST_EQ(c.val(), mod_fixnum(i << n));
                c = a >> n; TEST_EQ(c.val(), mod_fixnum(i >> n));
            }

            a = mod_fixnum(hi + i);
            b = j;
            c = a + b; TEST_EQ(c.val(), mod_fixnum(hi + i + j));
            c = a - b; TEST_EQ(c.val(), mod_fixnum(hi + i - j));
            c = a & b; TEST_EQ(c.val(), mod_fixnum(hi + i) & j);
            c = a | b; TEST_EQ(c.val(), mod_fixnum(hi + i) | j);
            c = a ^ b; TEST_EQ(c.val(), mod_fixnum(hi + i) ^ j);

            a = i;
            b = mod_fixnum(lo + j);
            c = a + b; TEST_EQ(c.val(), mod_fixnum(i + (lo + j)));
            c = a - b; TEST_EQ(c.val(), mod_fixnum(i - (lo + j)));
            c = a & b; TEST_EQ(c.val(), mod_fixnum(i & (lo + j)));
            c = a | b; TEST_EQ(c.val(), mod_fixnum(i | (lo + j)));
            c = a ^ b; TEST_EQ(c.val(), mod_fixnum(i ^ (lo + j)));
        }
    }
}

noinline void test_fixnum() {
    test_fixnum_assign();
    test_fixnum_unary_op();
    test_fixnum_binary_op();
}

noinline void test() {
    test_bool();
    test_double();
    test_float();
    test_fixnum();
}

int main() {
    test();
    return 0;
}

noinline Fixnum fixnum_add(Fixnum a, Fixnum b) {
    return a + b;
}

noinline Fixnum fixnum_sub(Fixnum a, Fixnum b) {
    return a - b;
}

noinline Fixnum fixnum_mul(Fixnum a, Fixnum b) {
    return a * b;
}

noinline Fixnum fixnum_rshift(Fixnum a, uint8_t count) {
    return a >> count;
}

