#ifndef CRYSP_IMPL_HPP
#define CRYSP_IMPL_HPP

#ifdef __GNUC__
#define noinline __attribute__((noinline))
#else
#define noinline
#endif

#ifdef __GNUC__
#define CRYSP_LIKELY(val) __builtin_expect(val, true)
#else
#define CRYSP_LIKELY(val) (val)
#endif

struct check_overflow_t {};

constexpr check_overflow_t check_overflow = {};

namespace impl {
    enum tag : uint64_t {
          // Int and Short methods depend on this exact value
          int_tag        = 0xFFFC000000000000ull, // negative quiet NaN
          int_mask       = int_tag,

          value_mask     = 0xFFFF000000000000ull,

          float_tag      = 0xFFF1000000000000ull, // negative signaling NaN
          short_tag      = 0xFFF2000000000000ull,
          type_tag       = 0xFFF3000000000000ull,
          rune_tag       = 0xFFF4000000000000ull,
          utf8_tag       = 0xFFF5000000000000ull,

          pointer_tag    = 0x7FF0000000000000ull, // positive signaling NaN (must skip zero payload = +inf)
          pointer_himask = 0xFFF0000000000000ull,
          pointer_mask   = 0xFFF000000000000Full,
          pointer_unmask = ~pointer_mask,

          struct_tag     = pointer_tag,
          pair_tag       = 0x7FF0000000000001ull,
          symbol_tag     = 0x7FF0000000000002ull,
          func_tag       = 0x7FF0000000000003ull,

#if defined(__aarch64__) || defined(__AARCH64EL__) || defined(__AARCH64BE__)
          fixed_addr_bits = 0x7FF0000000ull,
#else
          fixed_addr_bits = 0x7FF0ull << 4*sizeof(void *),
#endif

          nil_bits       = pair_tag + fixed_addr_bits,
          t_bits         = symbol_tag + 0x20 + fixed_addr_bits,
    };

    bool init();                /* throw(std::bad_alloc) */
    void * alloc(size_t bytes); /* throw(std::bad_alloc) */
    void throw_bad_alloc();     /* throw(std::bad_alloc) */
    void throw_bad_cast();      /* throw(std::bad_cast) */
    void throw_overflow_error(const char * type_name); /* throw(std::overflow_error) */
} // namespace impl


namespace type {
    enum id : uint32_t {
             unknown_id = 0,
             float_id   = 1,
             short_id   = 2,
             type_id    = 3,
             rune_id    = 4,
             utf8_id    = 5,
             double_id  = 0xE,
             int_id     = 0xF,
             struct_id  = 0x10,
             pair_id    = 0x11,
             symbol_id  = 0x12,
             func_id    = 0x13,
    };

} // namespace type

#endif // CRYSP_IMPL_HPP
