#ifndef CRYSP_NEW_HPP
#define CRYSP_NEW_HPP

#include <new>

#include "impl.hpp"

#define GCRYSP_NEW(class_, ...) \
    ((size_t)(void *)new (impl::alloc(sizeof(class_))) class_{__VA_ARGS__})

#endif // CRYSP_NEW_HPP
