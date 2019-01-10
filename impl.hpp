#ifndef CRYSP_IMPL_HPP
#define CRYSP_IMPL_HPP

#ifdef __GNUC__
#define noinline __attribute__((noinline))
#endif

struct check_overflow_t {};

constexpr check_overflow_t check_overflow = {};

namespace impl {
    enum {
        // Fixnum and Int methods depend on this exact value
        fixnum_tag   = 0xFFFC000000000000ull, // negative quiet NaN
        fixnum_mask  = fixnum_tag,

        value_mask   = 0xFFFF000000000000ull,

        float_tag    = 0xFFF1000000000000ull, // negative signaling NaN
        rune_tag     = 0xFFF2000000000000ull,

	// pointer methods depend on this exact value
        pointer_tag  = 0x7FF0000000000000ull, // positive signaling NaN (must skip zero payload = +inf)
        pointer_mask = 0xFFF0000000000000ull,

        struct_tag   = pointer_tag,
        cons_tag     = 0x7FF0000000000001ull,
        symbol_tag   = 0x7FF0000000000002ull,
        func_tag     = 0x7FF0000000000003ull,
        
        nil_bits     = cons_tag,
        t_bits       = symbol_tag + 0x20,
    };

    void throw_bad_cast(); /* throw(std::bad_cast) */
}

enum type_id {
    unknown_id = 0,
    double_id  = 1,
    fixnum_id  = 2,
    float_id   = 3,
    rune_id    = 4,
    struct_id  = 5,
    cons_id    = 6,
    symbol_id  = 7,
    func_id    = 8,
};
    

#endif // CRYSP_IMPL_HPP
