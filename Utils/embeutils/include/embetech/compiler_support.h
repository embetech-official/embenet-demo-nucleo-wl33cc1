/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   1.3.2
 *
 * This header provides portable macros for compiler-specific attributes such
 * as:
 * - EMBEUTILS_PACKED: Structure packing (no padding) - DEPRECATED
 * - EMBEUTILS_PACK_BEGIN and EMBEUTILS_PACK_END: Alternative structure packing (no padding)
 * - EMBEUTILS_NORETURN: Function does not return
 * - EMBEUTILS_WEAK: Weak symbol
 * - EMBEUTILS_NODISCARD: Warn if return value is unused
 * - EMBEUTILS_FALLTHROUGH: Intentional fallthrough in switch
 * - EMBEUTILS_INLINE: Always inline
 * - EMBEUTILS_RESTRICT: Restrict pointer
 * - EMBEUTILS_UNUSED: Mark argument as unused
 * - EMBEUTILS_NONNULL: Warn if argument is null
 * - EMBEUTILS_STATIC_ASSERT: Compile-time assertion
 * - EMBEUTILS_ALIGNAS: Alignment attribute
 * - EMBEUTILS_ALIGNOF: Alignment query
 */

#ifndef EMBEUTILS_COMPILER_SUPPORT_H_
#define EMBEUTILS_COMPILER_SUPPORT_H_

// Pull in C11 compatibility macros: alignas/alignof from <stdalign.h> and
// static_assert from <assert.h>. In C23 and C++ these are keywords, but in
// C11–C17 they are only available via these headers.
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#include <assert.h>
#include <stdalign.h>
#endif

// ===================== COMPILER DETECTION =====================
#if defined(__cplusplus) && (__cpp_attributes >= 200809L)
#define EMBEUTILS_HAS_STANDARD_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
#elif __STDC_VERSION__ >= 202311L
#define EMBEUTILS_HAS_STANDARD_ATTRIBUTE(attribute) __has_c_attribute(attribute)
#else
#define EMBEUTILS_HAS_STANDARD_ATTRIBUTE(attribute) 0
#endif

#if defined(__clang__)
#define EMBEUTILS_COMPILER_CLANG 1
#elif defined(__GNUC__)
#define EMBEUTILS_COMPILER_GCC 1
#elif defined(_MSC_VER)
#define EMBEUTILS_COMPILER_MSVC 1
#elif defined(__IAR_SYSTEMS_ICC__)
#define EMBEUTILS_COMPILER_IAR 1
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define EMBEUTILS_COMPILER_KEIL 1
#endif

/**
 * @def EMBEUTILS_PACKED
 * @deprecated Use @ref EMBEUTILS_PACK_BEGIN and @ref EMBEUTILS_PACK_END instead.
 *
 * Forces compiler to produce structure without padding (sizeof(structure) equals sum of sizeof(structure fields)).
 *
 * @note For MSVC use only with __declspec(align(1)) before struct, not for individual fields.
 *
 * @code
 * // Deprecated — prefer EMBEUTILS_PACK_BEGIN / EMBEUTILS_PACK_END
 * typedef struct {
 *     uint8_t  a;
 *     uint32_t b;
 * } EMBEUTILS_PACKED my_function_args_t;
 * @endcode
 */
#if defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_PACKED                                                                                                                             \
  _Pragma("GCC warning \"EMBEUTILS_PACKED is deprecated, use EMBEUTILS_PACK_BEGIN() and EMBEUTILS_PACK_END() instead\"") __attribute__((packed))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_PACKED                                                                                                                             \
  _Pragma("message(\"ERROR: EMBEUTILS_PACKED is not supported for MSVC compiler, use EMBEUTILS_PACK_BEGIN() and EMBEUTILS_PACK_END() instead\")")    \
      error error error
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_PACKED __packed
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_PACKED __packed
#else
#define EMBEUTILS_PACKED
#endif

/**
 * @def EMBEUTILS_PACK_BEGIN
 * Forces compiler to enable structure packing (no padding) from this point until next @ref EMBEUTILS_PACK_END is encountered.
 *
 * @code
 * EMBEUTILS_PACK_BEGIN()
 * typedef struct {
 *     uint8_t  a;
 *     uint32_t b;
 * } my_function_args_t;
 * EMBEUTILS_PACK_END()
 * @endcode
 */
#define EMBEUTILS_PACK_BEGIN() _Pragma("pack(push, 1)")

/**
 * @def EMBEUTILS_PACK_END
 * Restores compiler structure packing to the state before last @ref EMBEUTILS_PACK_BEGIN.
 *
 * @code
 * EMBEUTILS_PACK_BEGIN()
 * typedef struct { uint8_t a; uint32_t b; } my_function_args_t;
 * EMBEUTILS_PACK_END()
 * @endcode
 */
#define EMBEUTILS_PACK_END() _Pragma("pack(pop)")

/**
 * @def EMBEUTILS_WEAK
 * Marks the symbol as a weak definition, allowing it to be overridden by a strong definition at link time.
 *
 * @code
 * EMBEUTILS_WEAK void my_function(void) {
 *     // Default implementation — can be replaced by a strong definition in another TU
 * }
 * @endcode
 */
#if defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_WEAK __attribute__((weak))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_WEAK __declspec(selectany)
#elif defined(EMBEUTILS_COMPILER_IAR) || defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_WEAK __weak
#else
#define EMBEUTILS_WEAK
#endif

/**
 * @def EMBEUTILS_NORETURN
 * Informs compiler that the function may not return (i.e. has infinite loop, or throws).
 *
 * @note This macro MUST be placed BEFORE the return type of the function declaration.
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(noreturn)
#define EMBEUTILS_NORETURN [[noreturn]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_NORETURN __attribute__((noreturn))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_NORETURN __declspec(noreturn)
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_NORETURN __attribute__((noreturn))
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_NORETURN
#else
#define EMBEUTILS_NORETURN
#endif

/**
 * @def EMBEUTILS_NODISCARD
 * Warns if the return value of the function is not used.
 *
 * @note This macro MUST be placed BEFORE the return type of the function declaration.
 *       It cannot be placed after the parameter list.
 *
 * @code
 * EMBEUTILS_NODISCARD int my_function(void);
 * @endcode
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(nodiscard)
#define EMBEUTILS_NODISCARD [[nodiscard]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_NODISCARD __attribute__((warn_unused_result))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_NODISCARD _Check_return_
#else
#define EMBEUTILS_NODISCARD
#endif

/**
 * @def EMBEUTILS_FALLTHROUGH
 * Indicates that the fall-through from the previous case label is intentional
 * and should not be diagnosed by compilers that warn on implicit fallthrough.
 *
 * @code
 * switch (my_function()) {
 *     case 0:
 *         handle_zero();
 *         EMBEUTILS_FALLTHROUGH;
 *     case 1:
 *         handle_one_or_zero();
 *         break;
 * }
 * @endcode
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(fallthrough)
#define EMBEUTILS_FALLTHROUGH [[fallthrough]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_FALLTHROUGH __attribute__((fallthrough))
#else
#define EMBEUTILS_FALLTHROUGH
#endif

/**
 * @def EMBEUTILS_INLINE
 * Forces the compiler to always inline a function.
 *
 * @note For GCC and Clang, combine with the @c inline keyword:
 *       @code static EMBEUTILS_INLINE inline int foo(void) { return 0; } @endcode
 *       For MSVC and Keil, the macro already implies the @c inline keyword.
 */
#if defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_INLINE __attribute__((always_inline))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_INLINE __forceinline
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_INLINE __inline
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_INLINE __inline
#else
#define EMBEUTILS_INLINE
#endif

/**
 * @def EMBEUTILS_RESTRICT
 * Provides a portable means of using the C99 @c restrict keyword.
 *
 * @code
 * void my_function(uint8_t * EMBEUTILS_RESTRICT dst, uint8_t const * EMBEUTILS_RESTRICT src, size_t len);
 * @endcode
 */
#ifdef __cplusplus
#define EMBEUTILS_RESTRICT __restrict
#elif __STDC_VERSION__ >= 199901L
#define EMBEUTILS_RESTRICT restrict
#else
#define EMBEUTILS_RESTRICT
#endif

/**
 * @def EMBEUTILS_UNUSED(x)
 * Informs the compiler that the parameter @p x is intentionally unused.
 *
 * @param[in] x Name of the parameter to suppress unused-parameter warnings for.
 *
 * Usage: @code void function(int arg1, int EMBEUTILS_UNUSED(arg2)) { ... } @endcode
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(maybe_unused)
#define EMBEUTILS_UNUSED(x) x [[maybe_unused]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_UNUSED(x) x __attribute__((unused))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_UNUSED(x) __pragma(warning(suppress : 4100 4101)) x
#else
#define EMBEUTILS_UNUSED(x) x
#endif

/**
 * @def EMBEUTILS_NONNULL(...)
 * Warns when nullptr is provided as argument on given position.
 *
 * @param[in] ... list of argument indices to check against nullptr; when empty, ALL pointer arguments are marked as non-null.
 *
 * @code
 * // Both dst and src must not be null
 * void my_function(void *dst, void *src) EMBEUTILS_NONNULL();
 *
 * // Only src (argument 2) must not be null
 * void my_function2(void *dst, void *src) EMBEUTILS_NONNULL(2);
 * @endcode
 *
 * @note GNU/Clang compiler checks this only with -Wnonnull flag (which is included in -Wall).
 */
#if defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#else
#define EMBEUTILS_NONNULL(...)
#endif

/**
 * @def EMBEUTILS_STATIC_ASSERT(...)
 * Compile-time assertion.
 *
 * @code
 * EMBEUTILS_STATIC_ASSERT(sizeof(int) == 4, "int must be 4 bytes on this platform");
 * @endcode
 */
#if !defined(EMBEUTILS_STATIC_ASSERT)
#if (__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#define EMBEUTILS_STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#elif (__STDC_VERSION__ >= 201112L) || defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_STATIC_ASSERT(...) _Static_assert(__VA_ARGS__)
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_STATIC_ASSERT(...) __pragma(warning(suppress : 4127)) static_assert(__VA_ARGS__)
#elif defined(EMBEUTILS_COMPILER_KEIL) || defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#else
#define EMBEUTILS_STATIC_ASSERT(...) struct EMBEUTILS_static_assert_inactive
#endif
#endif

/**
 * @def EMBEUTILS_ALIGNAS(x)
 * Specifies the alignment requirement for a variable or type.
 *
 * @param[in] x Required alignment in bytes (must be a power of two).
 *
 * Usage: @code EMBEUTILS_ALIGNAS(16) uint8_t buffer[64]; @endcode
 */
#if !defined(EMBEUTILS_ALIGNAS)
#if (__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#define EMBEUTILS_ALIGNAS(x) alignas(x)
#elif __STDC_VERSION__ >= 201112L
#define EMBEUTILS_ALIGNAS(x) _Alignas(x)
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_ALIGNAS(x) __attribute__((aligned(x)))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_ALIGNAS(x) __declspec(align(x))
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_ALIGNAS(x) __align(x)
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_ALIGNAS(x) __attribute__((aligned(x)))
#else
#define EMBEUTILS_ALIGNAS(x)
#endif
#endif

/**
 * @def EMBEUTILS_ALIGNOF(x)
 * Returns the alignment requirement of the type or variable @p x.
 *
 * @param[in] x Type or variable to query.
 *
 * @code
 * size_t a = EMBEUTILS_ALIGNOF(double);
 * EMBEUTILS_STATIC_ASSERT(EMBEUTILS_ALIGNOF(uint32_t) == 4, "unexpected alignment");
 * @endcode
 */
#if !defined(EMBEUTILS_ALIGNOF)
#if (__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#define EMBEUTILS_ALIGNOF(x) alignof(x)
#elif __STDC_VERSION__ >= 201112L
#define EMBEUTILS_ALIGNOF(x) _Alignof(x)
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_ALIGNOF(x) __alignof__(x)
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_ALIGNOF(x) __alignof(x)
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_ALIGNOF(x) __alignof(x)
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_ALIGNOF(x) __alignof__(x)
#else
#define EMBEUTILS_ALIGNOF(x)
#endif
#endif

#endif // EMBEUTILS_COMPILER_SUPPORT_H_
