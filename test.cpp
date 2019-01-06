
#include <cstdio>
#include "test.hpp"

void test_failed(const char * str) {
    fprintf(stderr, "test failed: %s, actual [false], expected [true]", str);
}

void test_failed(const char * str, int64_t actual, int64_t expected) {
    fprintf(stderr, "test failed: %s, actual [%ld], expected [%ld]\n",
            str, actual, expected);
}

void test_failed(const char * str, T actual, T expected) {
    fprintf(stderr, "test failed: %s, actual [", str);
    actual.print(stderr);
    fputs("], expected [", stderr);
    expected.print(stderr);
    fputs("]\n", stderr);
}

