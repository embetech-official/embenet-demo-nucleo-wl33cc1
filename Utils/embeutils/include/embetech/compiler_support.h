#ifndef EMBEUTILS_COMPILER_SUPPORT_H_
#define EMBEUTILS_COMPILER_SUPPORT_H_

#ifdef __GNUC__

///@brief Forces compiler to produce structure without padding (sizeof(structure) equals sum of sizeof(structure fields))
#define EMBEUTILS_PACKED __attribute__((packed))

///@brief Informs compiler that the function may not return (i.e. has infinite loop, or throws)
#define EMBEUTILS_NORETURN __attribute__((noreturn))

///@brief Informs compiler that the symbol MUST be emitted as weak symbol
#define EMBEUTILS_WEAK __attribute__((weak))

///@brief Warns if the return value of the function is not used
#define EMBEUTILS_NODISCARD __attribute__((unused))

///@brief Indicates that the fall through from the previous case label is intentional and should not be diagnosed by a compiler that warns on
///fallthrough
#define EMBEUTILS_FALLTHROUGH __attribute__((fallthrough))

#define EMBEUTILS_INLINE __attribute__((always_inline))

#ifdef __cplusplus
///@brief provides portable mean of using C99 restrict keyword
#define EMBEUTILS_RESTRICT __restrict
#else
///@brief alias to C99 restrict keyword
#define EMBEUTILS_RESTRICT restrict
#endif

/**
 * @brief Informs compiler that the argument is unused
 * @param[in] x name of the argument to be marked as unused
 *
 * Usage: void function(int arg1, int EMBEUTILS_UNUSED(arg2)) { ... }
 */
#define EMBEUTILS_UNUSED(x) x __attribute__((unused))

/**
 * @brief Warns when nullptr is provided as argument on given position
 * @param[in] ... list of arguments indices to be checked against nullptr. When no argument is provided, ALL of the pointer arguments are marked as
 * non-null
 *
 * Usage:
 * void func1(void* dst, void* src) EMBEUTILS_NONNULL() - both dst and src MUST NOT take nullptr
 * void func2(void* dst, void* src) EMBEUTILS_NONNULL(2) - only src MUST NOT take nullptr
 * @note GNU compiler checks this only with -Wnonnull flag (which is included in -Wall)
 */
// #    define EMBEUTILS_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#define EMBEUTILS_NONNULL(...)

#else
#error "Compiler not supported (yet)"
#endif

#ifndef EMBEUTILS_PACKED
#if __GNUC__
/// Attribute to pack the structure (no padding between fields, and alignof(type) == 1)
#define EMBEUTILS_PACKED __attribute__((packed))
#else
#error "No known packed attribute for the compiler, please define EMBEUTILS_PACKED macro"
#endif
#endif

#ifndef EMBEUTILS_STATIC_ASSERT
#if(__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#include <assert.h>
/// Static assertion macro
#define EMBEUTILS_STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#elif(__STDC_VERSION__ >= 201112L) || defined(__GNUC__)
#define EMBEUTILS_STATIC_ASSERT(...) _Static_assert(__VA_ARGS__)
#else
#pragma message "No known static_assert support, please define EMBEUTILS_STATIC_ASSERT(x) macro"
#define EMBEUTILS_STATIC_ASSERT(...) struct EMBEUTILS_static_assert_inactive
#endif
#endif

#ifndef EMBEUTILS_ALIGNAS
#if(__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#include <stdalign.h>
/// Alignment attribute for the structure
#define EMBEUTILS_ALIGNAS(x) alignas(x)
#elif __STDC_VERSION__ >= 201112L
#define EMBEUTILS_ALIGNAS(x) _Alignas(x)
#elif __GNUC__
#define EMBEUTILS_ALIGNAS(x) __attribute__((aligned(x)))
#else
#error No known alignment attribute for the compiler, please define EMBEUTILS_ALIGNAS(x) macro
#endif
#endif

#ifndef EMBEUTILS_ALIGNOF
#if(__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#include <stdalign.h>
/// Alignment attribute for the structure
#define EMBEUTILS_ALIGNOF(x) alignof(x)
#elif __STDC_VERSION__ >= 201112L
#define EMBEUTILS_ALIGNOF(x) _Alignof(x)
#elif __GNUC__
#define EMBEUTILS_ALIGNOF(x) __alignof__(x)
#else
#error No known alignment attribute for the compiler, please define EMBEUTILS_ALIGNOF(x) macro
#endif
#endif

#endif
