#ifndef KR_DEBUG
#define KR_DEBUG

#define KR_DEBUG_SEPARATOR    '|'

void kr_debug_print_char(const char c);

/**
 * kr_debug_print_str - Prints a string as an escaped sequence of characters
 * @s: The provided string
 * @len: The provided string's length, null terminator excluded
 *
 * Each character is delimited by KR_DEBUG_SEPARATOR. The function converts
 * special characters and blanks into their respective escape sequences.
 * Whitespaces are printed as "·".
 * 
 * String's length is required for safety, strings that are not null-terminated
 * will be printed up to the provided length and will marked as unterminated.
 *
 * Examples:
 *   s: "   hello\t \n"
 *   output: [ ·|·|·|h|e|l|l|o|\t|·|\n|\0 ]
 *
 *   s: ""
 *   output: [ empty/invalid string ]
 *
 */
void kr_debug_print_str(const char s[], int len);

#endif /* KR_DEBUG */

