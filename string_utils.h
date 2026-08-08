#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>
#include <stddef.h>

// Reverses a string in-place.
void reverse_string(char *str);

// Checks if a string is a palindrome (case-insensitive).
bool is_palindrome(const char *str);

// Trims leading and trailing whitespace in-place.
void trim_whitespace(char *str);

// Counts the number of words in a string.
int count_words(const char *str);

// Converts string characters to uppercase in-place.
void to_uppercase(char *str);

#endif // STRING_UTILS_H
