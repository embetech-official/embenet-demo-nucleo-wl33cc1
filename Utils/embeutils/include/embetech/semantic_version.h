/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   1.3.2
 */

#ifndef EMBEUTILS_SEMANTIC_VERSION_H_
#define EMBEUTILS_SEMANTIC_VERSION_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Binary representation of a semantic version
 * The fields should be understood as described in https://semver.org
 */
typedef struct SemanticVersion {
  /// If different, the API is not compatible
  uint8_t major;

  /// Depicts new features that are backward compatible
  uint8_t minor;

  /// Bug fixes that are backward compatible
  uint16_t patch;

  /// Version metadata. Not used in the comparison, but may be used to identify a specific build, eg. a commit hash
  uint32_t id;
} SemanticVersion;

/**
 * Compares two semantic version strings and returns the result
 *
 * @param lhs left hand side of the comparison
 * @param rhs right hand side of the comparison
 * @return 1 if lhs > rhs
 * @return 0 if lhs == rhs
 * @return -1 if lhs < rhs
 *
 * @note the id field is ignored in the comparison
 *
 * @code
 * void my_function(void) {
 *     SemanticVersion v1 = {1, 2, 0, 0};
 *     SemanticVersion v2 = {1, 3, 0, 0};
 *     int result = SEMVER_Compare(v1, v2); // returns -1
 * }
 * @endcode
 */
static inline int SEMVER_Compare(SemanticVersion lhs, SemanticVersion rhs);

/**
 * Compares two semantic version strings and returns true if lhs is newer than rhs
 *
 * @param lhs left hand side of the comparison
 * @param rhs right hand side of the comparison
 * @return true if lhs > rhs
 *
 * @code
 * void my_function(void) {
 *     SemanticVersion current = {1, 0, 0, 0};
 *     SemanticVersion latest  = {1, 1, 0, 0};
 *     if (SEMVER_IsNewer(latest, current)) {
 *         // firmware update available
 *     }
 * }
 * @endcode
 */
static inline bool SEMVER_IsNewer(SemanticVersion lhs, SemanticVersion rhs);

/**
 * Returns true if @p v is a valid (non-sentinel) SemanticVersion.
 *
 * The all-zero value @c {0,0,0,0} is the invalid sentinel used by SEMVER_Parse
 * to signal parse failure, so it is considered invalid here.
 *
 * @param v version to test
 * @return @c true if @p v is not the zero sentinel
 */
static inline bool SEMVER_IsValid(SemanticVersion v);

/**
 * Parses a semantic version string and returns the result by value.
 *
 * Accepted format: @c "MAJOR.MINOR.PATCH" with an optional @c "+ID" suffix, where:
 * - @c MAJOR and @c MINOR are decimal values fitting in @c uint8_t,
 * - @c PATCH is a decimal value fitting in @c uint16_t,
 * - @c ID is a hexadecimal @c uint32_t (e.g. the first 8 digits of a git commit hash).
 *
 * The version @c "0.0.0" (which maps to the all-zero struct) is rejected as invalid.
 *
 * When the @c +ID suffix is absent, @c .id is set to @c 0.
 * When the @c '+' separator is present but the part after it cannot be parsed as a
 * hexadecimal number, @c .id is set to @c UINT32_MAX as an error sentinel and the
 * function still returns a valid version — the version triple itself was valid.
 *
 * @param[in] str null-terminated C string to parse.
 * @return parsed SemanticVersion on success.
 * @return @c {0,0,0,0} (the invalid sentinel) if the string was malformed,
 *         any numeric field overflowed its type, or the version was @c "0.0.0".
 *         Use SEMVER_IsValid() to distinguish success from failure.
 *
 * @code
 * void my_function(void) {
 *     SemanticVersion v = SEMVER_Parse("1.2.3");
 *     if (SEMVER_IsValid(v)) {
 *         // v.major == 1, v.minor == 2, v.patch == 3, v.id == 0
 *     }
 *     v = SEMVER_Parse("1.2.3+deadbeef");
 *     if (SEMVER_IsValid(v)) {
 *         // v.major == 1, v.minor == 2, v.patch == 3, v.id == 0xDEADBEEFu
 *     }
 *     v = SEMVER_Parse("1.2.3+xyz");
 *     if (SEMVER_IsValid(v)) {
 *         // v.id == UINT32_MAX  (invalid hex sentinel)
 *     }
 * }
 * @endcode
 */
static inline SemanticVersion SEMVER_Parse(char const *str);

// Inline implementation below
static inline int SEMVER_Compare(SemanticVersion lhs, SemanticVersion rhs) {

  if(lhs.major != rhs.major) {
    return (lhs.major > rhs.major) ? 1 : -1;
  }

  if(lhs.minor != rhs.minor) {
    return lhs.minor > rhs.minor ? 1 : -1;
  }

  if(lhs.patch != rhs.patch) {
    return lhs.patch > rhs.patch ? 1 : -1;
  }

  return 0;
}

static inline bool SEMVER_IsNewer(SemanticVersion lhs, SemanticVersion rhs) { return SEMVER_Compare(lhs, rhs) > 0; }

static inline bool SEMVER_IsValid(SemanticVersion v) { return (bool)((v.major != 0U) || (v.minor != 0U) || (v.patch != 0U) || (v.id != 0U)); }

static inline SemanticVersion SEMVER_Parse(char const *str) {
  SemanticVersion const invalid = {0U, 0U, 0U, 0U};
  char *end;

  unsigned long const major = strtoul(str, &end, 10);
  if(end == str || *end != '.' || major > UINT8_MAX) {
    return invalid;
  }
  str = end + 1;

  unsigned long const minor = strtoul(str, &end, 10);
  if(end == str || *end != '.' || minor > UINT8_MAX) {
    return invalid;
  }
  str = end + 1;

  unsigned long const patch = strtoul(str, &end, 10);
  if(end == str || patch > UINT16_MAX) {
    return invalid;
  }

  uint32_t id = 0U;
  if(*end == '+') {
    str = end + 1;
    unsigned long const parsed_id = strtoul(str, &end, 16);
    if(end == str) {
      id = UINT32_MAX;
      while(*end != '\0') {
        ++end;
      }
    } else {
      id = (uint32_t)parsed_id;
    }
  }

  if(*end != '\0') {
    return invalid;
  }

  SemanticVersion result = {(uint8_t)major, (uint8_t)minor, (uint16_t)patch, id};
  if(!SEMVER_IsValid(result)) {
    return invalid;
  }
  return result;
}

#ifdef __cplusplus
}
#endif

#endif
