#ifndef CRYSP_IMPL_HPP
#define CRYSP_IMPL_HPP

#ifdef __GNUC__
#define noinline __attribute__((noinline))
#endif

struct check_overflow_t {};

constexpr check_overflow_t check_overflow = {};

namespace impl {
    enum {
        // Int and Short methods depend on this exact value
        int_tag        = 0xFFFC000000000000ull, // negative quiet NaN
        int_mask       = int_tag,

        value_mask     = 0xFFFF000000000000ull,

        float_tag      = 0xFFF1000000000000ull, // negative signaling NaN
        short_tag      = 0xFFF2000000000000ull,
        rune_tag       = 0xFFF3000000000000ull,

        pointer_tag    = 0x7FF0000000000000ull, // positive signaling NaN (must skip zero payload = +inf)
        pointer_mask   = 0xFFF0000000000000ull,
        pointer_unmask = ~0xFFF000000000000Full,

        struct_tag     = pointer_tag,
        pair_tag       = 0x7FF0000000000001ull,
        symbol_tag     = 0x7FF0000000000002ull,
        func_tag       = 0x7FF0000000000003ull,
        
        nil_bits       = pair_tag + (0x7FF0ull << 4*sizeof(void *)),
        t_bits         = symbol_tag + (0x7FF0ull << 4*sizeof(void *)) + 0x20,
    };

    bool init();                /* throw(std::bad_alloc) */
    void * alloc(size_t bytes); /* throw(std::bad_alloc) */
    void throw_bad_alloc();     /* throw(std::bad_alloc) */
    void throw_bad_cast();      /* throw(std::bad_cast) */
    void throw_overflow_error(const char * type_name); /* throw(std::overflow_error) */
}

enum type_id {
    unknown_id = 0,
    double_id  = 1,
    int_id     = 2,
    float_id   = 3,
    short_id   = 4,
    rune_id    = 5,
    struct_id  = 6,
    pair_id    = 7,
    symbol_id  = 8,
    func_id    = 9,
};
    
#endif // CRYSP_IMPL_HPP
