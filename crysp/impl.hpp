#ifndef CRYSP_IMPL_HPP
#define CRYSP_IMPL_HPP

#include <cstddef> // size_t
#include <cstdint> // uint32_t, uint64_t

#define CRYSP_NS_START namespace crysp {
#define CRYSP_NS_END   } // namespace crysp
#define CRYSP_NS_USE   using namespace crysp;
#define CRYSP_NS       crysp::

CRYSP_NS_START

#ifdef __GNUC__
#define CRYSP_NOINLINE __attribute__((noinline))
#else
#define CRYSP_NOINLINE
#endif

#define CRYSP_NORETURN [[noreturn]]

#ifdef __GNUC__
#define CRYSP_LIKELY(val) __builtin_expect(val, true)
#else
#define CRYSP_LIKELY(val) (val)
#endif

struct check_overflow_t {};

constexpr check_overflow_t check_overflow = {};

namespace impl {
    enum tag : uint64_t {
          // Long methods depend on this exact value
          long_tag       = 0xFFFC000000000000ull, // negative quiet NaN
          long_mask      = long_tag,

          value_mask     = 0xFFFF000000000000ull,

          type_tag       = 0xFFF1000000000000ull, // negative signaling NaN
          float_tag      = 0xFFF2000000000000ull,
          int_tag        = 0xFFF3000000000000ull,
          rune_tag       = 0xFFF4000000000000ull,
          utf8_tag       = 0xFFF5000000000000ull,

          pointer_tag    = 0x7FF0000000000000ull, // positive signaling NaN (must skip zero payload = +inf)
          pointer_himask = 0xFFF0000000000000ull,
          pointer_mask   = 0xFFF000000000000Full,
          pointer_unmask = ~pointer_mask,

          obj_tag        = pointer_tag,
          pair_tag       = 0x7FF0000000000001ull,
          symbol_tag     = 0x7FF0000000000002ull,
          func_tag       = 0x7FF0000000000003ull,

	  /* start of fixed-address memory area containing nil, t ... */
#if defined(__aarch64__) || defined(__AARCH64EL__) || defined(__AARCH64BE__)	 
          fixed_addr_bits = 0x8000ull,
#else
          fixed_addr_bits = 0x10000ull,
#endif
          nil_bits       = pair_tag + fixed_addr_bits,
          t_bits         = symbol_tag + 0x20 + fixed_addr_bits,
    };

    bool init();                /* throw(std::bad_alloc) */
    void * alloc(size_t bytes); /* throw(std::bad_alloc) */
    CRYSP_NORETURN void throw_bad_alloc();     /* throw(std::bad_alloc) */
    CRYSP_NORETURN void throw_bad_cast();      /* throw(std::bad_cast) */
    CRYSP_NORETURN void throw_out_of_range(const char * message);  /* throw(std::out_of_range) */
    CRYSP_NORETURN void throw_overflow_error(const char * type_name); /* throw(std::overflow_error) */
    CRYSP_NORETURN void throw_runtime_error(const char * message);  /* throw(std::runtime_error) */
} // namespace impl


namespace type {
    enum id : uint32_t {
             t_id       = 0, // means "any type::id"
             type_id    = 1,
             float_id   = 2,
	     int_id     = 3,
             rune_id    = 4,
             utf8_id    = 5,
             double_id  = 0xE,
             long_id    = 0xF,
             obj_id     = 0x10,
             pair_id    = 0x11,
             symbol_id  = 0x12,
             func_id    = 0x13,
    };

} // namespace type

CRYSP_NS_END

#endif // CRYSP_IMPL_HPP
