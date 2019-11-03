#include <cstdio> // fwrite()
#include <cstring> // std::memcpy()

#include "new.hpp"
#include "string.hpp"

CRYSP_NS_START

String::String(Long size,
               const char data[]) /* throw(std::bad_alloc) */
    : T(impl::vector_tag
        | (size <= 0
           ? impl::empty_string_bits
           : GCRYSP_NEW_SIZE(sizeof(string) + size.val() * sizeof(char),
                             string, size, {}))) {
    if (size > 0) {
        string * s = reinterpret_cast<string *>(addr());
        if (data != nullptr) {
            std::memcpy(s->data, data, size.val());
        } else {
            std::memset(s->data, '\0', size.val());
        }
    }
}

char String::operator[](Long index) const {
    const string* s = reinterpret_cast<const string *>(addr());
    if (index < 0 || index >= s->size) {
        impl::throw_out_of_range("String index out of range");
    }
    return s->data[index.val()];
}

int String::print(FILE *out) const {
    const string * s = reinterpret_cast<const string *>(addr());
    if (s->size <= 0) {
        return 0;
    }
    return fwrite(s->data, sizeof(char), s->size.val(), out);
}

CRYSP_NS_END
