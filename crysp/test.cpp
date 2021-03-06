
#include <cstdio>
#include <cinttypes> // PRIx64

#include "test.hpp"
#include "type.hpp"

CRYSP_NS_START

void test_failed(const char * str) {
    fprintf(stderr, "test failed at %s,\tactual [false],\texpected [true]", str);
}

void test_failed(const char * str, int64_t actual, int64_t expected) {
    fprintf(stderr, "test failed at %s,\tactual int64_t(0x%" PRIx64
            "),\texpected int64_t(0x%" PRIx64 ")\n",
            str, actual, expected);
}

void test_failed(const char * str, T actual, T expected) {
    fprintf(stderr, "test failed at %s,\tactual %s(", str, actual.type().name());
    actual.print(stderr);
    fprintf(stderr, "),\texpected %s(", expected.type().name());
    expected.print(stderr);
    fputs(")\n", stderr);
}

CRYSP_NS_END
