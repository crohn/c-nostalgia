#ifndef KR_STRINGS
#define KR_STRINGS

/**
 * kr_is_blank_char - Test if provided character is blank
 * @c: The character to test
 *
 * Return:
 *   - 1 if the provided character is either newline, tab or whitespace
 *   - 0 otherwise
 */
int kr_is_blank_char(char c);


/**
 * kr_copy - Copy characters from a string buffer to another
 * @to: The target array to which characters are copied
 * @from: The source array from which characters are read
 *
 * Copies characters one at time from source to target array.
 *
 * IMPORTANT - the caller MUST ensure that:
 *   1. 'to' has enough space to hold the entire content of 'from', including
 *   the null terminator
 *   2. 'from' is null terminated
 *
 * This is an extremely unsafe function that exposes to potential buffer
 * overflow vulnerabilities. This function illustrates one of the fundamental
 * challenges in C programming, because it does not have any means to:
 *   1. know the capacity of the target buffer
 *   2. be sure that the source buffer is null-terminated
 *
 * The buffer overflow can lead to:
 *   1. Memory Access Violation - The function might read to or write from
 *   memory that it dous not own, resulting in a segmentation fault.
 *   2. Data Corruption - The function copy values values beyound 'from'
 *   memory, causing the corruption of other memory locations.
 *   3. Security Vulnerabilities - An attacker may be in control of 'from'
 *   buffer content and may be able to read sensitive information from adjacent
 *   memory locations.
 */
void kr_copy(char to[], const char from[]);


/**
 * kr_getline - Read input into a string buffer
 * @buffer: The character array to store the input
 * @max_len: The max number of characters to read, null terminator included
 *
 * Reads characters one at time from stdin until max_len - 1 characters ar read
 * or either EOF or newline characters are encountered. The character array
 * includes a newline character if encountered and is always null-terminated.
 *
 * Return:
 *   - the number of characters stored, null terminator exluded
 *   - -1 if EOF is encountered before any characters are read
 */
int kr_getline(char buffer[], int max_len);


/**
 * kr_reverse - Reverse the provided character string
 * @s: The provided character string
 *
 * Reverse the provided character string in place. 
 *
 * IMPORTANT - Because no string length is provided, the caller MUST ensure
 * that the provided string is null-terminated, otherwise the program may crash
 * due to illegal memory access.
 */
void kr_reverse(char s[]);


/**
 * kr_trim - Remove trailing blanks from provided character string
 * @line: The character string to trim
 * @len: Character string length, null terminator excluded
 *
 * Scans the provided string backward, removing blank characters until the
 * first non-blank character is found. If present, one single newline character
 * at the end of the string is preserved. Deletes entirely blank strings.
 *
 * Return:
 *   - The new string length after the trailing blank characters have been
 *   removed
 *   - 0 in case the provided string is empty
 */
int kr_trim(char s[], int len);

#endif /* KR_STRINGS */

