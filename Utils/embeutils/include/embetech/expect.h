/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   1.3.2
 */

#ifndef EMBEUTILS_EXPECT_H_
#define EMBEUTILS_EXPECT_H_

#include <embetech/compiler_support.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup expect_utility EXPECT error handling utility
 *
 * This tiny library provides simple utilities to manage error handling in a unified way across many software modules.
 *
 * <b>Rationale.</b>
 *
 * This header-only C library was born in order to provide a unified abstraction for writing sanity checks and handling
 * errors in a way that is easy to read to a human being. The idea was to be able to write short but meaningful statements
 * that can be easily understood and that could document the error checking process - especially the input argument
 * validation.
 *
 * <b>What may happen when you call a function?</b>
 *
 * We distinguish two types of things that may happen if you call a function:
 * - it runs throughout and produces a meaningful result that can be handled
 * - it aborts because an unexpected state was detected, which cannot be handled
 *
 * The first case includes both the situations in which the function ends with a success result as well as errors, that can
 * somehow be managed by the caller. For example, if you open a file for writing it may be successfully opened, but it may
 * also happen that the file is already open or the disk is write protected. Such cases usually end with an error code being
 * returned by the function to indicate, that it was unable to handle the request. This typically also includes situations
 * in which the input to the function is outside the valid range the function can handle - for example the filename was too long.
 * We will call these kind of errors <b><i>recoverable</i></b>
 *
 * But what should happen if during file access it turns out that the whole filesystem on the disk is corrupted and nothing
 * can be done to fix it? We call these situations as <b><i>unrecoverable</i></b> errors. In such case the application
 * might not be able to perform at all and should be aborted. This should however be considered as a rare and unexpected
 * behavior, where fixing it by the application is not feasible.
 *
 * <b>Handling recoverable errors with EXPECT</b>
 *
 * Below are some examples of function input validation with expect:
 *
 * @code
 * // This function returns one of 5 coefficients. For coeffNo >= 5 it always returns 0.0.
 * double getCoefficient(unsigned int coeffNo) {
 *     EXPECT(coeffNo < 5) OR_RETURN (0.0)
 *
 *     static double coeffTab[5] = { 1.0, 1.1, 1.2, 1.3, 1.4 };
 *
 *     return coeffTab[coeffNo];
 * }
 * @endcode
 *
 * <b>Handling unrecoverable errors with EXPECT</b>
 *
 * When unrecoverable error happens the expect library calls the @ref EXPECT_OnAbortHandler function that should be defined
 * by the user. The program must not continue operation after calling this function. A typical behavior of such function is to:
 * - go to a safe state
 * - log the error
 * - halt or reset the application
 *
 * In the above example, to convert to unrecoverable error we would change the implementation this way:
 *
 * @code
 * // This function returns one of 5 coefficients. For coeffNo >= 5 it causes the program to abort.
 * double getCoefficient(unsigned int coeffNo) {
 *     EXPECT(coeffNo < 5) OR_ABORT()
 *
 *     static double coeffTab[5] = { 1.0, 1.1, 1.2, 1.3, 1.4 };
 *
 *     return coeffTab[coeffNo];
 * }
 * @endcode
 *
 * <b>Standard and extra checks</b>
 *
 * For convenience the EXPECT library provides two levels of checks - standard checks and extra checks.
 * Extra checks are defined with the _EXTRA suffix. These checks are only performed if the EMBEUTILS_EXTRA_CHECKS
 * definition is visible when building the code.
 *
 * For example:
 * @code
 * int myFunc(const char* str) {
 *     EXPECT_EXTRA(NULL != str) OR_RETURN(0)
 * }
 *
 * @endcode
 *
 * <b>Runtime verbosity of abort handler</b>
 *
 * During initial development of the application, it is beneficial to quickly get information about the abort location and reason.
 * To enable this, you have to provide the following macro:
 * @code
 * EMBEUTILS_EXPECT_VERBOSE=1
 * @endcode
 *
 * @{
 */

#ifndef EMBEUTILS_EXPECT_VERBOSE
/**
 * When enabled, increases verbosity of information passed to EXPECT_OnAbortHandler
 * @note Enabling this macro WILL generate measurable memory overhead
 */
#define EMBEUTILS_EXPECT_VERBOSE 0
#endif

/**
 * @brief Abort handler called when an unrecoverable contract violation is detected.
 *
 * The program MUST NOT continue after this function is called. Typical implementations
 * log the error, enter a safe state, then halt or reset the system.
 *
 * @param[in] why  Message describing why the contract was violated.
 * @param[in] file Source file where the check was performed (or @c "<verbose-disabled>" if verbosity is off).
 * @param[in] line Source line where the check was performed (or @c 0 if verbosity is off).
 */
EMBEUTILS_NORETURN void EXPECT_OnAbortHandler(char const *why, char const *file, int line);

/**
 * @brief Checks whether the expression @p expr holds a true value.
 * @param[in] expr Expression to evaluate; the subsequent action is taken when it is false.
 * @note Must be followed by @ref OR_RETURN, or @ref OR_ABORT.
 *
 * @code
 * int my_function(int *ptr) {
 *     EXPECT(NULL != ptr) OR_RETURN(-1);
 *     return *ptr;
 * }
 * @endcode
 */
#define EXPECT(expr) if(!(expr))

/**
 * @def EXPECT_EXTRA(expr)
 * @copydoc EXPECT
 * As the evaluation of the expression may be time-consuming, these checks can be globally disabled by setting
 * @c EMBEUTILS_EXTRA_CHECKS to @c 0.
 */
#if (1 == EMBEUTILS_EXTRA_CHECKS)
#define EXPECT_EXTRA(expr) EXPECT(expr)
#else
#define EXPECT_EXTRA(expr) if(!(expr) && 0)
#endif

/**
 * @brief Directly calls the abort handler (EXPECT_OnAbortHandler) with the given reason.
 * @param[in] why Error message describing the violated contract
 * @note This macro must be preceded by either EXPECT or EXPECT_EXTRA.
 *
 * @code
 * void my_function(int *ptr) {
 *     EXPECT(NULL != ptr) EXPECT_ABORT("ptr must not be null");
 *     *ptr = 42;
 * }
 * @endcode
 */
#define EXPECT_ABORT(why) EXPECT_INTERNAL_CALL_ABORT_HANDLER(why)

/**
 * @brief Calls the abort handler (EXPECT_OnAbortHandler) with the given reason.
 * @param[in] why Error message describing the violated contract
 * @note This macro must be preceded by either EXPECT or EXPECT_EXTRA.
 *
 * @code
 * void my_function(int *ptr) {
 *     EXPECT(NULL != ptr) OR_ABORT("ptr must not be null");
 *     *ptr = 42;
 * }
 * @endcode
 */
#define OR_ABORT(why) EXPECT_INTERNAL_CALL_ABORT_HANDLER(why)

/**
 * @brief Returns from the enclosing function with the given value.
 * @param[in] retval Value to return when the EXPECT condition is false.
 * @note This macro must be preceded by either EXPECT or EXPECT_EXTRA.
 *
 * @code
 * int my_function(int *ptr) {
 *     EXPECT(NULL != ptr) OR_RETURN(-1);
 *     return *ptr;
 * }
 * @endcode
 */
#define OR_RETURN(retval) return retval

#if 1 == EMBEUTILS_EXPECT_VERBOSE
#define EXPECT_INTERNAL_CALL_ABORT_HANDLER(why) EXPECT_OnAbortHandler("" why, __FILE__, __LINE__)
#else
#define EXPECT_INTERNAL_CALL_ABORT_HANDLER(why) EXPECT_OnAbortHandler("<verbose-disabled>", "<verbose-disabled>", 0)
#endif

#ifdef __cplusplus
}
#endif

/** @} */

#endif
