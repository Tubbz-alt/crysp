#ifndef CRYSP_NEW_HPP
#define CRYSP_NEW_HPP

#include <new>

#include "impl.hpp"

#define GCRYSP_NEW(class_, ...) \
    ((size_t)(void *)new (CRYSP_NS impl::alloc(sizeof(class_))) class_{__VA_ARGS__})

#define GCRYSP_NEW_SIZE(size_, class_, ...)                              \
    ((size_t)(void *)new (CRYSP_NS impl::alloc(size_)) class_{__VA_ARGS__})

#endif // CRYSP_NEW_HPP
