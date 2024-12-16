#pragma once

namespace string
{

/**
 * @return Lenght of the string, ignoring trailing '\0'.
 */
unsigned strlen(const char* string);

/**
 * @return Occurrences of a character in string.
 */
unsigned count(const char* string, char sym);

/**
 * @return Compose two string, returning a merged one.
 */
char* join(const char* s1, const char* s2);

/**
 * @return Substring up to character
 */
char* substr_until(const char* string, char end_c);

/**
 * Create an array of strings in _parts, split on character.
 * @return parts count.
 */
int split(const char* string, char split_c, char*** _parts);

/**
 * @return true iff string matches the glob pattern
 *
 * Special characters:
 * - '*' wildcard
 * - '?' match any single character
 * - '[abc]' match one of the characters in brackets
 */
bool matches(const char* string, const char* pattern);

/**
 * @return String representation of n
 */
char* to_string(int n);

/**
 * @param fmt Format string, using % as placeholder
 * @return An expansion of all arguments in the format string.
 * 
 * Note: only integer arguments are supported
 * Example:
 * sprintf("x = %, y = %", 0, 1) -> "x = 0, x = 1"
 */
char* sprintf(const char* fmt, ...);

/**
 * Log string to file
 */
void flog(const char* file_path, const char* string);

} // namespace string
