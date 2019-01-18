#ifndef CRYSP_TEST_HPP
#define CRYSP_TEST_HPP

#include "crysp/t.hpp"

void test_failed(const char * str);
void test_failed(const char * str, T actual, T expected);
void test_failed(const char * str, int64_t actual, int64_t expected);

#define TEST_XSTR(arg) #arg
#define TEST_STR(arg)  TEST_XSTR(arg)

#define TEST_IS(pred) do {                                              \
        if (!(pred)) {                                                  \
            test_failed(__FILE__ ":" TEST_STR(__LINE__) ":\t"           \
                        #pred);                                         \
        }                                                               \
    } while (false)

#define TEST_EQ(actual, expected) do {                                  \
        if (!((actual) == (expected))) {                                \
            test_failed(__FILE__ ":" TEST_STR(__LINE__) ":\t"           \
                        #actual " == " #expected,                       \
                        (actual), (expected));                          \
        }                                                               \
    } while (false)

#endif // CRYSP_TEST_HPP
