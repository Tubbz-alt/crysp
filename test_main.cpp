#include <cstdio>
#include <cinttypes> // PRIX64

#include "cast.hpp"
#include "double.hpp"
#include "int.hpp"
#include "float.hpp"
#include "nil.hpp"
#include "rune.hpp"
#include "short.hpp"
#include "test.hpp"
#include "type.hpp"
#include "utf8.hpp"


noinline noinline void show(T x) {
    printf("%016" PRIX64 " = %s  \t", x.debug_bits(), x.type().name());
    x.print(stdout);
    putchar('\n');
}

noinline void test_bool() {
    show(nil);
    show(t);
}

noinline void test_cons() {
    Pair c = Pair{t, nil};
    show(c);
    TEST_EQ(c->first, t);
    TEST_EQ(c->second, nil);
}

noinline void show_double() {
    show(Double{0.0});
    show(Double{0.5});
    show(Double{1.0});
    show(Double{1023.0});
    show(Double{1.0/0.0}); // inf
    show(Double{-0.0/0.0}); // -NaN
}

noinline void show_float() {
    show(Float{0.0f});
    show(Float{0.5f});
    show(Float{1.0f});
    show(Float{1023.0f});
    show(Float{1.0f/0.0f}); // inf
    show(Float{-0.0f/0.0f}); // -NaN
}

template<class Num, class num>
noinline void test_int_assign(Num lo, Num hi) {
    Num n;
    T t;
    TEST_EQ(n.val(), 0);
    for (num i = -50; i <= 50; i++) {
        n = i;
        TEST_EQ(n.val(), i);
        t = n;
        TEST_EQ(n, t);
        TEST_EQ(n, cast<Num>(t));
        if (n.val() >= -1 && n.val() <= 1)
            show(n);
    }
    show(hi);
    show(lo);
}

int64_t mod(int64_t i) {
    i &= 0x3FFFFFFFFFFFFll; // truncate to 50 bits
    return (i << 14) >> 14; // sign extend
}

int32_t mod(int32_t i) {
    return i;
}

template<class Num, class num>
noinline void test_int_unary_op(num lo, num hi) {
    Num n;
    // test ++ and --
    for (num i = -1024; i <= 1024; i++) {
        n = i;
        n++; TEST_EQ(n.val(), i + 1);
        ++n; TEST_EQ(n.val(), i + 2);
        n--; TEST_EQ(n.val(), i + 1);
        --n; TEST_EQ(n.val(), i + 0);
    }
    // test overflow and underflow
    n = hi;
    n++; TEST_EQ(n.val(), lo);
    n--; TEST_EQ(n.val(), hi);
    ++n; TEST_EQ(n.val(), lo);
    --n; TEST_EQ(n.val(), hi);

    // test += and -=
    for (num i = -50; i <= 50; i++) {
        for (num j = -50; j <= 50; j++) {
            n = i;
            n += j; TEST_EQ(n.val(), i + j);
            n -= i; TEST_EQ(n.val(), j);
            n += Num{i}; TEST_EQ(n.val(), i + j);
            n -= Num{j}; TEST_EQ(n.val(), i);
        }
    }

    // test overflow and underflow
    for (num i = -50; i <= 0; i++) {
        for (num j = -70; j <= 70; j++) {
            n = hi - i;
            n += Num{j}; TEST_EQ(n.val(), mod(hi - i + j));
            n -= Num{j}; TEST_EQ(n.val(), mod(hi - i));
            n += j; TEST_EQ(n.val(), mod(hi - i + j));
            n -= j; TEST_EQ(n.val(), mod(hi - i));
        }
    }

    // test unary + - !
    for (num i = -1024; i <= 1024; i++) {
        n = i;
        n = +n; TEST_EQ(n.val(), +i);
        n = -n; TEST_EQ(n.val(), -i);
        n = !n; TEST_EQ(n.val(), !-i);
    }
    // test overflow and underflow
    for (num i = 0; i <= 16; i++) {
        n = hi - i;
        n = -n; TEST_EQ(n.val(), -hi + i);

        n = lo + i;
        n = -n; TEST_EQ(n.val(), mod(-lo - i));
    }
}

template<class Num, class num>
noinline void test_int_binary_op0(num i, num j) {
    Num a{i}, b{j}, c;

    c = a + b; TEST_EQ(c.val(), mod(i + j));
    c = a + j; TEST_EQ(c.val(), mod(i + j));
    c = i + b; TEST_EQ(c.val(), mod(i + j));
            
    c = a - b; TEST_EQ(c.val(), mod(i - j));
    c = a - j; TEST_EQ(c.val(), mod(i - j));
    c = i - b; TEST_EQ(c.val(), mod(i - j));
            
    c = a * b; TEST_EQ(c.val(), mod(i * j));
    c = a * j; TEST_EQ(c.val(), mod(i * j));
    c = i * b; TEST_EQ(c.val(), mod(i * j));

    if (j != 0) {
        // do not divide <type>_min by -1,
        // it may generate SIGFPE
        if (mod(i-1) < i || j != -1) {
            c = a / b; TEST_EQ(c.val(), mod(i / j));
            c = a / j; TEST_EQ(c.val(), mod(i / j));
            c = i / b; TEST_EQ(c.val(), mod(i / j));

            c = a % b; TEST_EQ(c.val(), mod(i % j));
            c = a % j; TEST_EQ(c.val(), mod(i % j));
            c = i % b; TEST_EQ(c.val(), mod(i % j));
        }
    }
    c = a & b; TEST_EQ(c.val(), mod(i & j));
    c = a & j; TEST_EQ(c.val(), mod(i & j));
    c = i & b; TEST_EQ(c.val(), mod(i & j));

    c = a | b; TEST_EQ(c.val(), mod(i | j));
    c = a | j; TEST_EQ(c.val(), mod(i | j));
    c = i | b; TEST_EQ(c.val(), mod(i | j));

    c = a ^ b; TEST_EQ(c.val(), mod(i ^ j));
    c = a ^ j; TEST_EQ(c.val(), mod(i ^ j));
    c = i ^ b; TEST_EQ(c.val(), mod(i ^ j));
}

template<class Num, class num>
noinline void test_int_binary_op(num lo, num hi) {
    Num a, b, c;

    for (num i = -50; i <= 50; i++) {
        for (num j = -50; j <= 50; j++) {
            a = i;
            b = j;

            TEST_EQ(a < b, i < j);
            TEST_EQ(a < j, i < j);
            TEST_EQ(i < b, i < j);

            if (j >= 0) {
                uint8_t n = uint8_t(j);
                c = a << n; TEST_EQ(c.val(), mod(i << n));
                c = a >> n; TEST_EQ(c.val(), mod(i >> n));
            }

            test_int_binary_op0<Num, num>(i,           j);
            test_int_binary_op0<Num, num>(mod(hi + i), j);
            test_int_binary_op0<Num, num>(i,           mod(lo + j));
            test_int_binary_op0<Num, num>(mod(hi + i), mod(lo + j));
        }
    }
}

noinline void test_int() {
    test_int_assign<Int, int64_t>(int_min, int_max);
    test_int_unary_op<Int, int64_t>(int_min.val(), int_max.val());
    test_int_binary_op<Int, int64_t>(int_min.val(), int_max.val());
}

noinline void test_short() {
    test_int_assign<Short, int32_t>(short_min, short_max);
    test_int_unary_op<Short, int32_t>(short_min.val(), short_max.val());
    test_int_binary_op<Short, int32_t>(short_min.val(), short_max.val());
}

template<class FL, class fl>
noinline void test_float_unary_op() {
    FL n;
    // test ++ and --
    for (fl i = -1024; i <= 1024; i++) {
        n = i;
        n++; TEST_EQ(n.val(), i + 1);
        ++n; TEST_EQ(n.val(), i + 2);
        n--; TEST_EQ(n.val(), i + 1);
        --n; TEST_EQ(n.val(), i + 0);
    }

    // test += and -=
    for (fl i = -50; i <= 50; i++) {
        for (fl j = -50; j <= 50; j++) {
            n = i;
            n += j; TEST_EQ(n.val(), i + j);
            n -= i; TEST_EQ(n.val(), j);
        }
    }

    // test unary + - !
    for (fl i = -1024; i <= 1024; i++) {
        n = i;
        n = +n; TEST_EQ(n.val(), +i);
        n = -n; TEST_EQ(n.val(), -i);
        n = !n; TEST_EQ(n.val(), !-i);
    }
}

template<class FL, class fl>
noinline void test_float_binary_op(fl i, fl j) {
    FL a = i, b = j, c;

    TEST_EQ(a < b, i < j);
    TEST_EQ(a < j, i < j);
    TEST_EQ(i < b, i < j);
            
    c = a + b; TEST_EQ(c.val(), i + j);
    c = a + j; TEST_EQ(c.val(), i + j);
    c = i + b; TEST_EQ(c.val(), i + j);

    c = a - b; TEST_EQ(c.val(), i - j);
    c = a - j; TEST_EQ(c.val(), i - j);
    c = i - b; TEST_EQ(c.val(), i - j);
    
    c = a * b; TEST_EQ(c.val(), i * j);
    c = a * j; TEST_EQ(c.val(), i * j);
    c = i * b; TEST_EQ(c.val(), i * j);

    if (j != 0) {
        c = a / b; TEST_EQ(c.val(), i / j);
        c = a / j; TEST_EQ(c.val(), i / j);
        c = i / b; TEST_EQ(c.val(), i / j);
    }
}

noinline void show_rune() {
    show(Rune{' '});
    show(Rune{'A'});
    show(Rune{'Z'});
    show(Rune{0xA2}); // cent symbol
    show(Rune{0x20AC}); // Euro sign
    show(Rune{0xFFFD}); // replacement character
    show(Rune{0x10348}); // Gothic letter Hwair
    show(Rune{0x10FFFF}); // highest codepoint

    show(Utf8{' '});
    show(Utf8{'A'});
    show(Utf8{'Z'});
    show(Utf8{0xA2}); // cent symbol
    show(Utf8{0x20AC}); // Euro sign
    show(Utf8{0xFFFD}); // replacement character
    show(Utf8{0x10348}); // Gothic letter Hwair
    show(Utf8{0x10FFFF}); // highest codepoint
}

noinline void test_rune() {
    for (rune i = 0x80; i <= 0x10FFFF; i++) {
        Rune r{i};
        Utf8 u{r};
        TEST_EQ(r.val(), i);
        TEST_EQ(u.val_rune(), i);
        TEST_EQ(Rune{u}, r);
    }
    show_rune();
}

template<class FL, class fl>
noinline void test_float_binary_op() {
    for (fl i = -20; i <= 20; i += 0.25) {
        for (fl j = -20; j <= 20; j += 0.25) {
            test_float_binary_op<FL, fl>(i, j);
        }
    }
}

noinline void test_double() {
    show_double();
    test_float_unary_op<Double, double>();
    test_float_binary_op<Double, double>();
}

noinline void test_float() {
    show_float();
    test_float_unary_op<Float, float>();
    test_float_binary_op<Float, float>();
}

noinline void test_type() {
    show(Type{});
    show(Float{}.type());
    show(short_max.type());
    show(t.type().type());
    show(Rune{}.type());
    show(Utf8{}.type());
    show(Double{}.type());
    show(int_max.type());
    show(nil.type());
    show(t.type());
}

noinline void test() {
    test_bool();
    test_cons();
    test_double();
    test_float();
    test_short();
    test_type();
    test_rune();
    test_int();
}

int main() {
    test();
    return 0;
}

