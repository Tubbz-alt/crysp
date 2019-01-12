#include <cstdio>
#include <cinttypes> // PRIX64

#include "cast.hpp"
#include "double.hpp"
#include "fixint.hpp"
#include "float.hpp"
#include "nil.hpp"
#include "smallint.hpp"
#include "test.hpp"
#include "type.hpp"


noinline noinline void show(T x) {
    printf("%016" PRIX64 " = ", x.debug_bits());
    x.print(stdout);
    putchar('\n');
}

noinline void test_bool() {
    show(nil);
    show(t);
}

noinline void test_cons() {
    Cons c = Cons{t, nil};
    show(c);
    TEST_EQ(c->first, t);
    TEST_EQ(c->rest, nil);
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

noinline void test_fixint_assign() {
    Fixint n;
    T t;
    TEST_EQ(n.val(), 0);
    TEST_EQ(n, Smallint{});
    for (int32_t i = -50; i <= 50; i++) {
        n = i;
        TEST_EQ(n.val(), i);
        TEST_EQ(n, Smallint{i});
        t = Smallint{i};
        TEST_EQ(n, t);
        TEST_EQ(n, cast<Fixint>(t));
        if (n.val() >= -1 && n.val() <= 1)
            show(n);
    }
    show(fixint_max);
    show(fixint_min);
    show(smallint_max);
    show(smallint_min);
}

int64_t mod_fixint(int64_t i) {
    i &= 0x3FFFFFFFFFFFFll;
    return (i << 14) >> 14; // sign extend
}
 
noinline void test_fixint_unary_op() {
    Fixint n;
    // test ++ and --
    for (int32_t i = -1024; i <= 1024; i++) {
        n = i;
        n++; TEST_EQ(n.val(), i + 1);
        ++n; TEST_EQ(n.val(), i + 2);
        n--; TEST_EQ(n.val(), i + 1);
        --n; TEST_EQ(n.val(), i + 0);
    }
    // test overflow and underflow
    int64_t lo = fixint_min.val();
    int64_t hi = fixint_max.val();
    n = hi;
    n++; TEST_EQ(n.val(), lo);
    n--; TEST_EQ(n.val(), hi);
    ++n; TEST_EQ(n.val(), lo);
    --n; TEST_EQ(n.val(), hi);

    // test += and -=
    for (int32_t i = -50; i <= 50; i++) {
        for (int32_t j = -50; j <= 50; j++) {
            n = i;
            n += j; TEST_EQ(n.val(), i + j);
            n -= i; TEST_EQ(n.val(), j);
            n += Fixint{i}; TEST_EQ(n.val(), i + j);
            n -= Fixint{j}; TEST_EQ(n.val(), i);
        }
    }

    // test overflow and underflow
    for (int32_t i = -50; i <= 0; i++) {
        for (int32_t j = -70; j <= 70; j++) {
            n = hi - i;
            n += Fixint{j}; TEST_EQ(n.val(), mod_fixint(hi - i + j));
            n -= Fixint{j}; TEST_EQ(n.val(), mod_fixint(hi - i));
            n += j; TEST_EQ(n.val(), mod_fixint(hi - i + j));
            n -= j; TEST_EQ(n.val(), mod_fixint(hi - i));
        }
    }

    // test unary + - !
    for (int32_t i = -1024; i <= 1024; i++) {
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
        n = -n; TEST_EQ(n.val(), mod_fixint(-lo - i));
    }
}

noinline void test_fixint_binary_op(int64_t i, int64_t j) {
    Fixint a{i}, b{j}, c;

    c = a + b; TEST_EQ(c.val(), mod_fixint(i + j));
    c = a + j; TEST_EQ(c.val(), mod_fixint(i + j));
    c = i + b; TEST_EQ(c.val(), mod_fixint(i + j));
            
    c = a - b; TEST_EQ(c.val(), mod_fixint(i - j));
    c = a - j; TEST_EQ(c.val(), mod_fixint(i - j));
    c = i - b; TEST_EQ(c.val(), mod_fixint(i - j));
            
    c = a * b; TEST_EQ(c.val(), mod_fixint(i * j));
    c = a * j; TEST_EQ(c.val(), mod_fixint(i * j));
    c = i * b; TEST_EQ(c.val(), mod_fixint(i * j));

    if (j != 0) {
        c = a / b; TEST_EQ(c.val(), mod_fixint(i / j));
        c = a / j; TEST_EQ(c.val(), mod_fixint(i / j));
        c = i / b; TEST_EQ(c.val(), mod_fixint(i / j));

        c = a % b; TEST_EQ(c.val(), mod_fixint(i % j));
        c = a % j; TEST_EQ(c.val(), mod_fixint(i % j));
        c = i % b; TEST_EQ(c.val(), mod_fixint(i % j));
    }
    c = a & b; TEST_EQ(c.val(), mod_fixint(i & j));
    c = a & j; TEST_EQ(c.val(), mod_fixint(i & j));
    c = i & b; TEST_EQ(c.val(), mod_fixint(i & j));

    c = a | b; TEST_EQ(c.val(), mod_fixint(i | j));
    c = a | j; TEST_EQ(c.val(), mod_fixint(i | j));
    c = i | b; TEST_EQ(c.val(), mod_fixint(i | j));

    c = a ^ b; TEST_EQ(c.val(), mod_fixint(i ^ j));
    c = a ^ j; TEST_EQ(c.val(), mod_fixint(i ^ j));
    c = i ^ b; TEST_EQ(c.val(), mod_fixint(i ^ j));
}

noinline void test_fixint_binary_op() {
    Fixint a, b, c;

    int64_t lo = fixint_min.val();
    int64_t hi = fixint_max.val();
    
    for (int64_t i = -50; i <= 50; i++) {
        for (int64_t j = -50; j <= 50; j++) {
            a = i;
            b = j;

            TEST_EQ(a < b, i < j);
            TEST_EQ(a < j, i < j);
            TEST_EQ(i < b, i < j);

            if (j >= 0) {
                uint8_t n = uint8_t(j);
                c = a << n; TEST_EQ(c.val(), mod_fixint(i << n));
                c = a >> n; TEST_EQ(c.val(), mod_fixint(i >> n));
            }

            test_fixint_binary_op(i,                  j);
            test_fixint_binary_op(mod_fixint(hi + i), j);
            test_fixint_binary_op(i,                  mod_fixint(lo + j));
            test_fixint_binary_op(mod_fixint(hi + i), mod_fixint(lo + j));
        }
    }
}

noinline void test_fixint() {
    test_fixint_assign();
    test_fixint_unary_op();
    test_fixint_binary_op();
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


noinline void test() {
    test_bool();
    test_cons();
    test_double();
    test_float();
    test_fixint();
}

int main() {
    test();
    return 0;
}

