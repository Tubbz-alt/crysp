#ifndef CRYSP_IMPL_HPP
#define CRYSP_IMPL_HPP

namespace impl {
    enum {
        tag_mask     = 0xFFFF000000000000ull,

        fixnum_tag   = 0x7FF0000000000000ull, // positive signaling NaN
        float_tag    = 0x7FF1000000000000ull,
        rune_tag     = 0x7FF2000000000000ull,

        pointer_tag  = 0xFFFF000000000000ull, // negative quiet NaN
        pointer_mask = 0xFFFF00000000000Full,
        
        struct_tag   = pointer_tag,
        cons_tag     = 0xFFFF000000000001ull,
        symbol_tag   = 0xFFFF000000000002ull,
        func_tag     = 0xFFFF000000000003ull,
        
        nil_bits     = cons_tag,
        t_bits       = symbol_tag + 0x18,
    };
}

#endif // CRYSP_IMPL_HPP
