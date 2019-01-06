#ifndef CRYSP_IMPL_HPP
#define CRYSP_IMPL_HPP

namespace impl {
    enum {
        // Fixnum methods depend on this exact value
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
}

#endif // CRYSP_IMPL_HPP
