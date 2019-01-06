#ifndef CRYSP_TEST_HPP
#define CRYSP_TEST_HPP

#include "t.hpp"

void test_failed(const char * str);
void test_failed(const char * str, T actual, T expected);
void test_failed(const char * str, int64_t actual, int64_t expected);

#define TEST_IS(pred) do {                                              \
        if (!(pred)) {                                                  \
            test_failed(#pred);                                         \
        }                                                               \
    } while (false)

#define TEST_EQ(actual, expected) do {                                  \
        if (!((actual) == (expected))) {                                \
            test_failed(#actual " == " #expected,                       \
                        (actual), (expected));                          \
        }                                                               \
    } while (false)

#endif // CRYSP_TEST_HPP
